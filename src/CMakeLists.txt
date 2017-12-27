set(FOLDER_NAME "src")

ADD_SUBDIRECTORY(include)

INCLUDE_DIRECTORIES(include)

ADD_EXECUTABLE(MemRepairBaselineDemo MemRepairBaselineDemo.cpp)
ADD_EXECUTABLE(MemRepairBaselineBenchmark MemRepairBaselineBenchmark.cpp)

TARGET_LINK_LIBRARIES(MemRepairBaselineDemo MemRepair)
TARGET_LINK_LIBRARIES(MemRepairBaselineBenchmark MemRepair)




