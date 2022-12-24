cmake_minimum_required(VERSION ${MY_CMAKE_VERSION})

project(cmsis-posix-project)

add_library(
	cmsis STATIC
	api/cmsis_generic.c
	api/cmsis_kernel.c
	api/cmsis_message_queue.c
	api/cmsis_mutexes.c
	api/cmsis_semaphores.c
	api/cmsis_thread.c
	core/cmsis_wasm_memory.c
	core/cmsis_wasm_message_queue.c
	core/cmsis_wasm_queue.c
	core/cmsis_wasm_thread_sync.c
	core/cmsis_wasm_time.c
	core/wasm.c
)

target_include_directories(
	cmsis
	PRIVATE ${CMSIS_INTERFACE_DIR}
	PRIVATE ${PROJECT_SOURCE_DIR}/include
	PRIVATE ${PROJECT_SOURCE_DIR}/api
	PRIVATE ${PROJECT_SOURCE_DIR}/core
	PRIVATE ${PROJECT_SOURCE_DIR}/config
	PRIVATE ${PROJECT_SOURCE_DIR}/../../../library/include
)