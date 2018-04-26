#include <life_cycle.h>
#include <context.h>

#include <clover.h>
#include <unistd.h>

#include <insigne/driver.h>
#include <insigne/render.h>
#include <insigne/buffers.h>

namespace calyx {

	void initialize()
	{
		CLOVER_VERBOSE("app init");
	}

	void run(event_buffer_t* i_evtBuffer)
	{
		CLOVER_VERBOSE("app run");
		
		insigne::initialize_driver();
		insigne::initialize_render_thread();
		insigne::wait_for_initialization();

		u32 event = 0;
		static u32 si = 0;
		while (true) {
			while (i_evtBuffer->try_pop_into(event)) {
				si++;
				CLOVER_VERBOSE("%d", event + si);
				usleep(16000);
			}
		}
	}

	void clean_up()
	{
		CLOVER_VERBOSE("app cleanup");
	}

}
