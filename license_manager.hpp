#pragma once

#include "com/ibm/License/LicenseManager/server.hpp"
#include <sdbusplus/bus.hpp>
#include <sdbusplus/server/object.hpp>
#include <sdeventplus/source/event.hpp>

namespace license {
namespace manager {

class LicenseMgr;
using iface = sdbusplus::server::object::object<
    sdbusplus::com::ibm::License::server::LicenseManager>;

/** @class Manager
 *  @brief Implementation for the license manager
 */
class LicenseMgr : public iface {
public:
  LicenseMgr() = delete;
  LicenseMgr(const LicenseMgr &) = delete;
  LicenseMgr &operator=(const LicenseMgr &) = delete;
  LicenseMgr(LicenseMgr &&) = delete;
  LicenseMgr &operator=(LicenseMgr &&) = delete;
  virtual ~LicenseMgr() = default;

  /** @brief Constructor to put object onto bus at a dbus path.
   *  @param[in] bus - Bus to attach to.
   *  @param[in] path - Path to attach at.
   */
  LicenseMgr(sdbusplus::bus_t& bus, sdeventplus::Event &event,
             const char *path)
      : iface(bus, path), bus(bus), event(event), objectPath(path){};

  std::string licenseString(std::string value) override {
    // On updating new license string set licenseActivationStatus to Pending,
    // So that status of new license activation can be updated.
    sdbusplus::com::ibm::License::server::LicenseManager::
        licenseActivationStatus(Status::Pending);
    return sdbusplus::com::ibm::License::server::LicenseManager::licenseString(
        value);
  }

private:
  /** @brief sdbusplus DBus bus connection. */
  sdbusplus::bus_t& bus;
  // sdevent Event handle
  sdeventplus::Event &event;
  /** @brief object path */
  std::string objectPath;
};

} // namespace manager
} // namespace license
