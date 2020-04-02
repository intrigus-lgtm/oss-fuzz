// Copyright 2020 Google LLC
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//      http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

#include <Alembic/AbcCoreFactory/All.h>
#include <Alembic/AbcCoreOgawa/All.h>
#include <Alembic/AbcGeom/All.h>
#include <Alembic/AbcMaterial/All.h>

#include <err.h>
#include <errno.h>
#include <fcntl.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

using Alembic::AbcCoreAbstract::PropertyHeader;
using Alembic::AbcCoreAbstract::PropertyType;
using Alembic::AbcCoreFactory::IFactory;
using Alembic::AbcGeom::C4fArraySamplePtr;
using Alembic::AbcGeom::IArchive;
using Alembic::AbcGeom::IC4fGeomParam;
using Alembic::AbcGeom::ICompoundProperty;
using Alembic::AbcGeom::ICurves;
using Alembic::AbcGeom::ICurvesSchema;
using Alembic::AbcGeom::IFaceSet;
using Alembic::AbcGeom::IFaceSetSchema;
using Alembic::AbcGeom::IN3fGeomParam;
using Alembic::AbcGeom::index_t;
using Alembic::AbcGeom::Int32ArraySamplePtr;
using Alembic::AbcGeom::IObject;
using Alembic::AbcGeom::IPolyMesh;
using Alembic::AbcGeom::IPolyMeshSchema;
using Alembic::AbcGeom::ISubD;
using Alembic::AbcGeom::ISubDSchema;
using Alembic::AbcGeom::IV2fGeomParam;
using Alembic::AbcGeom::IXform;
using Alembic::AbcGeom::IXformSchema;
using Alembic::AbcGeom::M44d;
using Alembic::AbcGeom::M44f;
using Alembic::AbcGeom::N3fArraySamplePtr;
using Alembic::AbcGeom::ObjectHeader;
using Alembic::AbcGeom::P3fArraySamplePtr;
using Alembic::AbcGeom::UInt32ArraySamplePtr;
using Alembic::AbcGeom::V2fArraySamplePtr;
using Alembic::AbcMaterial::IMaterial;
using Alembic::AbcMaterial::IMaterialSchema;

void printMeshAttributes(const IPolyMeshSchema& schema) {
  const size_t meshPropertyCount = schema.getNumProperties();
  std::cout << "  Mesh Property Count: " << meshPropertyCount << ".\n";

  for (size_t p = 0; p < meshPropertyCount; p++) {
    const PropertyHeader& header = schema.getPropertyHeader(p);
    const PropertyType pType = header.getPropertyType();
    const std::string& name = header.getName();

    std::cout << "  Property[" << p << "] name: " << name << "\n";

    if (name == "P") {
      std::cout << "    Sample Count: " << schema.getNumSamples() << "\n";
    } else if (name == "N") {
      std::cout << "    Sample Count: "
                << schema.getNormalsParam().getNumSamples() << "\n";
    } else if (name == "uv" || name == "st") {
      std::cout << "    Sample Count: " << schema.getUVsParam().getNumSamples()
                << "\n";
    } else if (name == ".arbGeomParams") {
      // additional geometry elements (color sets, additional texture
      // coordinates)
      const ICompoundProperty geoParam = schema.getArbGeomParams();
      const size_t geoPropCount = geoParam.getNumProperties();
      std::cout << "    GeomParams Count: " << geoPropCount << ".\n";

      for (size_t g = 0; g < geoPropCount; g++) {
        const PropertyHeader& headerGeo = geoParam.getPropertyHeader(g);
        const std::string& nameGeo = headerGeo.getName();
        std::cout << "    arbGeomParam[" << g << "] name: " << nameGeo << "\n";
        // TODO(jchernobieff):
        // Getting the sample count here is more involved, should it be done
        // for this test?
      }
    }
  }
}

void printSubDAttributes(const ISubDSchema& schema) {
  const size_t subdPropertyCount = schema.getNumProperties();
  std::cout << "  SubD Property Count: " << subdPropertyCount << ".\n";

  for (size_t p = 0; p < subdPropertyCount; p++) {
    const PropertyHeader& header = schema.getPropertyHeader(p);
    const PropertyType pType = header.getPropertyType();
    const std::string& name = header.getName();

    std::cout << "  Property[" << p << "] name: " << name << "\n";

    if (name == "P") {
      std::cout << "    Sample Count: " << schema.getNumSamples() << "\n";
    } else if (name == "uv" || name == "st") {
      std::cout << "    Sample Count: " << schema.getUVsParam().getNumSamples()
                << "\n";
    } else if (name == ".arbGeomParams") {
      // additional geometry elements (color sets, additional texture
      // coordinates)
      const ICompoundProperty geoParam = schema.getArbGeomParams();
      const size_t geoPropCount = geoParam.getNumProperties();
      std::cout << "    GeomParams Count: " << geoPropCount << ".\n";

      for (size_t g = 0; g < geoPropCount; g++) {
        const PropertyHeader& headerGeo = geoParam.getPropertyHeader(g);
        const std::string& nameGeo = headerGeo.getName();
        std::cout << "    arbGeomParam[" << g << "] name: " << nameGeo << "\n";
        // TODO(jchernobieff):
        // Getting the sample count here is more involved, should it be done
        // for this test?
      }
    }
  }
}

void printCurvesAttributes(const ICurvesSchema& schema) {
  const size_t propertyCount = schema.getNumProperties();
  std::cout << "  Curves Property Count: " << propertyCount << ".\n";

  for (size_t p = 0; p < propertyCount; p++) {
    const PropertyHeader& header = schema.getPropertyHeader(p);
    const PropertyType pType = header.getPropertyType();
    const std::string& name = header.getName();

    std::cout << "  Property[" << p << "] name: " << name << "\n";

    if (name == "P") {
      std::cout << "    Sample Count: " << schema.getNumSamples() << "\n";
    } else if (name == "N") {
      std::cout << "    Sample Count: "
                << schema.getNormalsParam().getNumSamples() << "\n";
    } else if (name == "uv" || name == "st") {
      std::cout << "    Sample Count: " << schema.getUVsParam().getNumSamples()
                << "\n";
    } else if (name == ".arbGeomParams") {
      // additional geometry elements (color sets, additional texture
      // coordinates)
      const ICompoundProperty geoParam = schema.getArbGeomParams();
      const size_t geoPropCount = geoParam.getNumProperties();
      std::cout << "    GeomParams Count: " << geoPropCount << ".\n";

      for (size_t g = 0; g < geoPropCount; g++) {
        const PropertyHeader& headerGeo = geoParam.getPropertyHeader(g);
        const std::string& nameGeo = headerGeo.getName();
        std::cout << "    arbGeomParam[" << g << "] name: " << nameGeo << "\n";
      }
    }
  }
}

void printPolyMesh(const IObject& node) {
  const ObjectHeader& header = node.getHeader();
  const IPolyMesh mesh(node.getParent(), header.getName());
  const IPolyMeshSchema& schema = mesh.getSchema();

  // Mesh properties
  printMeshAttributes(schema);
}

void printSubD(const IObject& node) {
  const ObjectHeader& header = node.getHeader();
  const ISubD mesh(node.getParent(), header.getName());
  const ISubDSchema& schema = mesh.getSchema();

  printSubDAttributes(schema);
  std::cout << "  Subdivision Scheme: " << schema.getSubdivisionSchemeProperty()
            << "\n";
  std::cout << "  Face Varying Interpolate Boundary: "
            << schema.getFaceVaryingInterpolateBoundaryProperty() << "\n";
  std::cout << "  Face Varying Propagate Corners: "
            << schema.getFaceVaryingPropagateCornersProperty() << "\n";
  std::cout << "  Interpolate Boundary: "
            << schema.getInterpolateBoundaryProperty() << "\n";
}

void printFaceSet(const IObject& node) {
  const ObjectHeader& header = node.getHeader();
  const IFaceSet faceSet(node.getParent(), header.getName());
  const IFaceSetSchema& schema = faceSet.getSchema();

  std::cout << "  Sample Count: " << schema.getNumSamples() << "\n";
}

void printCurves(const IObject& node) {
  const ObjectHeader& header = node.getHeader();
  const ICurves curves(node.getParent(), header.getName());
  const ICurvesSchema& schema = curves.getSchema();

  printCurvesAttributes(schema);
}

void printXform(const IObject& node) {
  const ObjectHeader& header = node.getHeader();
  const IXform xform(node.getParent(), header.getName());
  const IXformSchema& schema = xform.getSchema();

  std::cout << "  Sample Count: " << schema.getNumSamples() << "\n";
  std::cout << "  Number of Ops: " << schema.getNumOps() << "\n";
}

void printMaterial(const IObject& node) {
  const ObjectHeader& header = node.getHeader();
  IMaterial material(node.getParent(), header.getName());
  IMaterialSchema& schema = material.getSchema();

  std::vector<std::string> targetNames;
  size_t targetCount = targetNames.size();
  std::cout << "  Target Count: " << targetCount << "\n";

  for (size_t t = 0; t < targetCount; t++) {
    std::cout << "  Target[" << t << "] name: " << targetNames[t] << "\n";

    std::vector<std::string> shaderTypes;
    schema.getShaderTypesForTarget(targetNames[t], shaderTypes);
    const size_t shaderTypeCount = shaderTypes.size();
    std::cout << "    Shader Type Count: " << shaderTypeCount << "\n";
    for (size_t s = 0; s < shaderTypeCount; s++) {
      std::cout << "    Shader Type [" << s << "] name: " << shaderTypes[s]
                << "\n";

      // At this point we can print out the shader if desired...
      // but that seems excessive.

      ICompoundProperty parameters =
          schema.getShaderParameters(targetNames[t], shaderTypes[s]);
      const size_t parameterCount = parameters.getNumProperties();
      std::cout << "    Shader Parameter Count: " << parameterCount << "\n";
    }
  }
}

void printNodes(const IObject& node) {
  const ObjectHeader& header = node.getHeader();
  // Print the general node information.
  std::cout << "Node name: " << header.getName() << "\n";
  std::cout << "Node full name: " << header.getFullName() << "\n";
  std::cout << "MetaData: " << header.getMetaData().serialize() << "\n";

  // Print the type specific information.
  if (Alembic::AbcGeom::IPolyMesh::matches(header)) {
    printPolyMesh(node);
  } else if (Alembic::AbcGeom::ISubD::matches(header)) {
    printSubD(node);
  } else if (Alembic::AbcGeom::IFaceSet::matches(header)) {
    printFaceSet(node);
  } else if (Alembic::AbcGeom::ICurves::matches(header)) {
    printCurves(node);
  } else if (Alembic::AbcGeom::IXform::matches(header)) {
    printXform(node);
  } else if (Alembic::AbcMaterial::IMaterial::matches(header)) {
    printMaterial(node);
  } else {  // Miscellaneous nodes such as the root.
    std::cout << "Object type ignored.\n";
  }

  // Print the child headers.
  const size_t childCount = node.getNumChildren();
  for (size_t i = 0; i < childCount; i++) {
    printNodes(node.getChild(i));
  }
}

void printInfo(const char* file) {
  // Load the Alembic archive and verify that it is valid.
  IFactory factory;
  IArchive archive = factory.getArchive(file);

  bool fileValid = archive.valid();
  std::cout << "\nfile " << file << (fileValid ? "" : " (invalid)")
            << ":\n\n";

  if (fileValid) {
    std::cout << "file name: " << archive.getName() << "\n";
    // printNodes(archive.getTop());
  }
}

int ignore_stdout(void) {
  int fd = open("/dev/null", O_WRONLY);
  if (fd == -1) {
    warn("open(\"/dev/null\") failed");
    return -1;
  }

  int ret = 0;
  if (dup2(fd, STDOUT_FILENO) == -1) {
    warn("failed to redirect stdout to /dev/null\n");
    ret = -1;
  }

  if (close(fd) == -1) {
    warn("close");
    ret = -1;
  }

  return ret;
}

int delete_file(const char *pathname) {
  int ret = unlink(pathname);
  if (ret == -1) {
    warn("failed to delete \"%s\"", pathname);
  }

  free((void *)pathname);

  return ret;
}

char *buf_to_file(const uint8_t *buf, size_t size) {
  char *pathname = strdup("/dev/shm/fuzz-XXXXXX");
  if (pathname == nullptr) {
    return nullptr;
  }

  int fd = mkstemp(pathname);
  if (fd == -1) {
    warn("mkstemp(\"%s\")", pathname);
    free(pathname);
    return nullptr;
  }

  size_t pos = 0;
  while (pos < size) {
    int nbytes = write(fd, &buf[pos], size - pos);
    if (nbytes <= 0) {
      if (nbytes == -1 && errno == EINTR) {
        continue;
      }
      warn("write");
      goto err;
    }
    pos += nbytes;
  }

  if (close(fd) == -1) {
    warn("close");
    goto err;
  }

  return pathname;

err:
  delete_file(pathname);
  return nullptr;
}

static bool initialized = false;

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  if (!initialized) {
    ignore_stdout();
    initialized = true;
  }

  const char* file = buf_to_file(data, size);
  if (file == NULL) {
    exit(EXIT_FAILURE);
  }

  try {
    printInfo(file);
  } catch (const std::exception& e) {
    std::cout << e.what() << std::endl;
  }

  if (delete_file(file) != 0) {
    exit(EXIT_FAILURE);
  }

  return EXIT_SUCCESS;
}
