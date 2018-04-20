#include "memory_system.h"

#include <clover.h>

#include <refrain2.h>

#include <context.h>

helich::memory_manager							g_MemoryManager;

// allocators for amborella
namespace calyx {
	allocators									g_allocators;
}

// allocators for clover
namespace clover {
	LinearAllocator								g_LinearAllocator;
}

// allocators for refrain2
namespace refrain2 {
	FreelistAllocator							g_TaskAllocator;
	FreelistAllocator							g_TaskDataAllocator;
};

namespace helich {
	void init_memory_system()
	{
		using namespace helich;
		g_MemoryManager.initialize(
				memory_region<calyx::stack_allocator_t> 	{ "calyx/subsystems",			SIZE_MB(16),	&calyx::g_allocators.subsystems_allocator },
				memory_region<clover::LinearAllocator>		{ "clover/allocator",			SIZE_MB(32),	&clover::g_LinearAllocator },
				memory_region<refrain2::FreelistAllocator>	{ "refrain2/task",				SIZE_MB(4),		&refrain2::g_TaskAllocator },
				memory_region<refrain2::FreelistAllocator>	{ "refrain2/taskdata",			SIZE_MB(32),	&refrain2::g_TaskDataAllocator }
				);
	}
}
