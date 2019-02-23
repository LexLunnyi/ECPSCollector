import os
from conans import ConanFile, CMake

class ECPSCollectorConan(ConanFile):
    name = "ECPSCollector"
    version = "0.0.1"
    description = "Collector of signals: electrocardiogram, plethysmogram, spirogram"
    generators = "cmake"
    no_copy_source = True
    requires = "sdl2/2.0.8@bincrafters/stable"
    my_defs = {"build_type": "testing", "version_string": version}

    def imports(self):
        self.copy("*.a", "../lib", "lib")
        self.copy("*.h", "../include", "include")

    def build(self):
        cmake = CMake(self)

        if "ECPS_COLLECTOR_BUILD" in os.environ :
            self.my_defs["build_type"]=os.environ["ECPS_COLLECTOR_BUILD"]

        cmake.configure(source_folder="../", build_folder="../", defs = self.my_defs)
        cmake.build()

    def package(self):
        self.copy("../ECPSCollector*", dst=".", keep_path=False)

    def deploy(self):
        self.copy("ECPSCollector*")
        self.copy_deps("*.a")
