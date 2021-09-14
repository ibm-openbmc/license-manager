#include "license_manager.hpp"

#include <sdeventplus/event.hpp>

//#include <phosphor-logging/elog-errors.hpp>
//#include <phosphor-logging/elog.hpp>
//#include <phosphor-logging/log.hpp>
//#include <xyz/openbmc_project/Common/error.hpp> 

int main()
{
    auto bus = sdbusplus::bus::new_default();
    std::string busName = "com.ibm.License.Manager";
    bus.request_name(busName.c_str());

    static constexpr auto objPath = "/com/ibm/license";

    // Get default event loop
    auto event = sdeventplus::Event::get_default();

    // Attach the bus to sd_event to service user requests
    bus.attach_event(event.get(), SD_EVENT_PRIORITY_NORMAL);

    // Add sdbusplus ObjectManager
    sdbusplus::server::manager::manager objManager(bus, objPath);

    license::manager::LicenseMgr manager(bus, event, objPath);
    event.loop();
    return 0;
}
