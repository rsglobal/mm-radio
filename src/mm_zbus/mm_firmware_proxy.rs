//! # DBus interface proxy for: `org.freedesktop.ModemManager1.Modem.Firmware`
//!
//! This code was generated by `zbus-xmlgen` `3.1.0` from DBus introspection data.
//! Source: `org.freedesktop.ModemManager1.Modem.Firmware.xml`.
//!
//! You may prefer to adapt it, instead of using it verbatim.
//!
//! More information can be found in the
//! [Writing a client proxy](https://dbus.pages.freedesktop.org/zbus/client.html)
//! section of the zbus documentation.
//!

use zbus::dbus_proxy;

#[dbus_proxy(
    default_service = "org.freedesktop.ModemManager1",
    interface = "org.freedesktop.ModemManager1.Modem.Firmware",
    assume_defaults = true,
    gen_blocking = false
)]
trait Firmware {
    /// List method
    fn list(
        &self,
    ) -> zbus::Result<(String, Vec<std::collections::HashMap<String, zbus::zvariant::OwnedValue>>)>;

    /// Select method
    fn select(&self, uniqueid: &str) -> zbus::Result<()>;

    /// UpdateSettings property
    #[dbus_proxy(property)]
    fn update_settings(
        &self,
    ) -> zbus::Result<(u32, std::collections::HashMap<String, zbus::zvariant::OwnedValue>)>;
}
