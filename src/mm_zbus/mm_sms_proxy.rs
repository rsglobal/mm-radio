//! # DBus interface proxy for: `org.freedesktop.ModemManager1.Sms`
//!
//! This code was generated by `zbus-xmlgen` `3.1.0` from DBus introspection data.
//! Source: `org.freedesktop.ModemManager1.Sms.xml`.
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
    interface = "org.freedesktop.ModemManager1.Sms",
    assume_defaults = true,
    gen_blocking = false
)]
trait Sms {
    /// Send method
    fn send(&self) -> zbus::Result<()>;

    /// Store method
    fn store(&self, storage: u32) -> zbus::Result<()>;

    /// Class property
    #[dbus_proxy(property)]
    fn class(&self) -> zbus::Result<i32>;

    /// Data property
    #[dbus_proxy(property)]
    fn data(&self) -> zbus::Result<Vec<u8>>;

    /// DeliveryReportRequest property
    #[dbus_proxy(property)]
    fn delivery_report_request(&self) -> zbus::Result<bool>;

    /// DeliveryState property
    #[dbus_proxy(property)]
    fn delivery_state(&self) -> zbus::Result<u32>;

    /// DischargeTimestamp property
    #[dbus_proxy(property)]
    fn discharge_timestamp(&self) -> zbus::Result<String>;

    /// MessageReference property
    #[dbus_proxy(property)]
    fn message_reference(&self) -> zbus::Result<u32>;

    /// Number property
    #[dbus_proxy(property)]
    fn number(&self) -> zbus::Result<String>;

    /// PduType property
    #[dbus_proxy(property)]
    fn pdu_type(&self) -> zbus::Result<u32>;

    /// SMSC property
    #[dbus_proxy(property, name = "SMSC")]
    fn smsc(&self) -> zbus::Result<String>;

    /// ServiceCategory property
    #[dbus_proxy(property)]
    fn service_category(&self) -> zbus::Result<u32>;

    /// State property
    #[dbus_proxy(property)]
    fn state(&self) -> zbus::Result<u32>;

    /// Storage property
    #[dbus_proxy(property)]
    fn storage(&self) -> zbus::Result<u32>;

    /// TeleserviceId property
    #[dbus_proxy(property)]
    fn teleservice_id(&self) -> zbus::Result<u32>;

    /// Text property
    #[dbus_proxy(property)]
    fn text(&self) -> zbus::Result<String>;

    /// Timestamp property
    #[dbus_proxy(property)]
    fn timestamp(&self) -> zbus::Result<String>;

    //    /// Validity property
    //    #[dbus_proxy(property)]
    //    fn validity(&self) -> zbus::Result<(u32, zbus::zvariant::OwnedValue)>;
}
