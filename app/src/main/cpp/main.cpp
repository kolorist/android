#include <life_cycle.h>
#include <context.h>

#include <clover.h>

namespace calyx {

	void initialize()
	{
		CLOVER_VERBOSE("app init");
	}

	void run(event_buffer_t* i_evtBuffer)
	{
		CLOVER_VERBOSE("app run");
		u32 event = 0;
		while (true) {
			while (i_evtBuffer->try_pop_into(event)) {
				CLOVER_VERBOSE("%d", event);
			}
		}
	}

	void clean_up()
	{
		CLOVER_VERBOSE("app cleanup");
	}

}
