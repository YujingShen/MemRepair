SET(FOLDER_NAME "include")

SET(LIB_FILES Graph.cpp MemRepair.cpp FaultGen.cpp)

ADD_LIBRARY(MemRepair SHARED ${LIB_FILES})

SET(TEST_SRCS     
	TestIO.cpp 
	TestFlowInsert.cpp
	TestMaxFlowMinCost.cpp 
	TestBipartiteGraph.cpp
	TestGraphBuild.cpp
	TestBaselineSimple.cpp
	TestFaultGen.cpp
)


foreach(testSrc ${TEST_SRCS})
    get_filename_component(testName ${testSrc} NAME_WE)
	add_executable(${testName} ${testSrc})

	target_link_libraries(${testName} MemRepair)

	add_test(${testName} ${testName})
endforeach(testSrc)