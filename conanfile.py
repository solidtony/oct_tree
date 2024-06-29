from conan import ConanFile
from conan.tools.cmake import CMake
from conan.tools.cmake import cmake_layout
from conan.tools.cmake import CMakeToolchain

class Recipe(ConanFile):
    settings = "os", "compiler", "build_type", "arch"
    generators = "CMakeDeps"

    def requirements(self):
        if not self.conf.get("tools.build:skip_test", default=False):
            self.requires("gtest/1.14.0")

    def generate(self):
        tc = CMakeToolchain(self, generator="Ninja Multi-Config")
        tc.generate()

    def build_requirements(self):
        self.tool_requires("cmake/3.26.5")
        self.tool_requires("ninja/1.11.1")

    def layout(self):
        cmake_layout(self, generator="Ninja Multi-Config")

    def build(self):
        cmake = CMake(self)
        cmake.configure()
        cmake.build()
        cmake.test()
