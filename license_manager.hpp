#pragma once

#include "com/ibm/License/LicenseManager/server.hpp"
#include <sdbusplus/bus.hpp>
#include <sdbusplus/server/object.hpp>
#include <sdeventplus/source/event.hpp>

namespace license
{
namespace manager
{

class LicenseMgr;
using iface = sdbusplus::server::object::object<
    sdbusplus::com::ibm::License::server::LicenseManager>;


/** @class Manager
 *  @brief Implementation for the license manager
 */
class LicenseMgr : public iface
{
  public:
    LicenseMgr() = delete;
    LicenseMgr(const LicenseMgr&) = delete;
    LicenseMgr& operator=(const LicenseMgr&) = delete;
    LicenseMgr(LicenseMgr&&) = delete;
    LicenseMgr& operator=(LicenseMgr&&) = delete;
    virtual ~LicenseMgr() = default;

    /** @brief Constructor to put object onto bus at a dbus path.
     *  @param[in] bus - Bus to attach to.
     *  @param[in] path - Path to attach at.
     */
    LicenseMgr(sdbusplus::bus::bus& bus, sdeventplus::Event& event,
              const char* path) :
        iface(bus, path,true),
        bus(bus), event(event), objectPath(path){
        };

  private:
    /** @brief sdbusplus DBus bus connection. */
    sdbusplus::bus::bus& bus;
    // sdevent Event handle
    sdeventplus::Event& event;
    /** @brief object path */
    std::string objectPath;
};

} // namespace manager
} // namespace license
