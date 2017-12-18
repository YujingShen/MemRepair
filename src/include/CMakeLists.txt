SET(FOLDER_NAME "include")

SET(LIB_FILES
    Graph.cpp
	MemRepair.cpp
)

ADD_LIBRARY(MemRepairLib SHARED LIB_FILES)