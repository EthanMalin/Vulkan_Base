#pragma once

#include <vector>
#include <fstream>
#include <iostream>
#include <unordered_map>
#include <vulkan/vulkan.h>

#define TINYOBJLOADER_IMPLEMENTATION
#include <tiny_obj_loader.h>

#include "Vertex.h"

std::vector<char> readFile(const std::string& filename) {
  std::ifstream file(filename, std::ios::ate | std::ios::binary);
  if (!file.is_open()) {
    throw std::runtime_error("failed to open file: " + filename);
  }
  size_t fileSize = (size_t)file.tellg();
  std::vector<char> buffer(fileSize);
  file.seekg(0);
  file.read(buffer.data(), fileSize);
  file.close();
  return buffer;
}

// functions that load and call the debug utils messenger extensions
// this allows us to set callback functions for error messages of various severities and types.
VkResult CreateDebugUtilsMessengerEXT(VkInstance instance, const VkDebugUtilsMessengerCreateInfoEXT* pCreateInfo, const VkAllocationCallbacks* pAllocator, VkDebugUtilsMessengerEXT* pDebugMessenger) {
  auto func = (PFN_vkCreateDebugUtilsMessengerEXT)vkGetInstanceProcAddr(instance, "vkCreateDebugUtilsMessengerEXT");
  if (func != nullptr) {
    return func(instance, pCreateInfo, pAllocator, pDebugMessenger);
  }
  else {
    return VK_ERROR_EXTENSION_NOT_PRESENT;
  }
}
void DestroyDebugUtilsMessengerEXT(VkInstance instance, VkDebugUtilsMessengerEXT debugMessenger, const VkAllocationCallbacks* pAllocator) {
  auto func = (PFN_vkDestroyDebugUtilsMessengerEXT)vkGetInstanceProcAddr(instance, "vkDestroyDebugUtilsMessengerEXT");
  if (func != nullptr) {
    func(instance, debugMessenger, pAllocator);
  }
}

struct Mesh {
  std::vector<Vertex> vertices;
  std::vector<uint32_t> indices;
};


void loadModel(const std::string &model_path, std::vector<Vertex> &vertices, std::vector<uint32_t> &indices) {
  tinyobj::attrib_t attrib;
  std::vector<tinyobj::shape_t> shapes;
  std::vector<tinyobj::material_t> materials;
  std::string warn, err;
  if (!tinyobj::LoadObj(&attrib, &shapes, &materials, &warn, &err, model_path.c_str())) {
    std::cout << "tinyobj load model failed: " + model_path << std::endl;
    throw std::runtime_error(warn + err);
  }

  std::unordered_map<Vertex, uint32_t> uniqueVertices{};
  for (const auto& shape : shapes) {
    for (const auto& index : shape.mesh.indices) {
      Vertex vertex{};
      vertex.pos = {
		    attrib.vertices[3 * index.vertex_index + 0],
		    attrib.vertices[3 * index.vertex_index + 1],
		    attrib.vertices[3 * index.vertex_index + 2]
      };
      vertex.normal = {
		       attrib.normals[3 * index.normal_index + 0],
		       attrib.normals[3 * index.normal_index + 1],
		       attrib.normals[3 * index.normal_index + 2]
      };
      vertex.texCoord = {
			 attrib.texcoords[2 * index.texcoord_index + 0],
			 1.0f - attrib.texcoords[2 * index.texcoord_index + 1]
      };
      vertex.color = { 1.0f, 1.0f, 1.0f };

      if (uniqueVertices.count(vertex) == 0) {
	uniqueVertices[vertex] = static_cast<uint32_t>(vertices.size());
	vertices.push_back(vertex);
      }
      indices.push_back(uniqueVertices[vertex]);
    }
  }
}


