use regex::Regex;
use rocket::serde::Serialize;
use rocket::serde::Deserialize;

use std::net::IpAddr;

#[derive(Serialize, Deserialize)]
pub struct Device{
    pub devicename: String,
    pub mac: String,
    pub ip: String,
    pub port: String
}

impl Device{    
    pub fn new(devicename: String, mac: String, ip: String, port: String) -> Result<Device, errors::ParseError>{
        if Self::check_mac(&mac) && Self::check_ip(&ip){
            Ok(Device{devicename: devicename, mac:mac, ip: ip, port: port})
        }else{
            Err(errors::ParseError)
        }
    }

    //checks, if the format of the mac string is correct
    fn check_mac(mac: &String) -> bool{
        let mac_regex = Regex::new(r"^([0-9a-fA-F]{2}:{1,2}){5}[0-9a-fA-F]{2}$").unwrap();
        if !mac_regex.is_match(mac){
            return false;
        }

        true
    }

    //checks, if the format of the ip is correct
    fn check_ip(ip: &String) -> bool{
        if let Ok(_) = ip.parse::<IpAddr>(){
            true
        }else{
            false
        }
    }
}

pub mod database{
    use pickledb::{PickleDb, PickleDbDumpPolicy};
    use super::Device;
    use errors::UnauthorizedDeviceError;

    const DB_PATH: &str = "devices.db";

    //TODO later: check inside a file, if a mac address or device name is allowed to connect to the server
    //TODO save hash of values, isntead clear text
    const _AUTHORIZED_DEVICES_PATH: &str = "authorized_devices.txt";

    pub fn open_database() -> PickleDb{
        match PickleDb::load_json(DB_PATH, PickleDbDumpPolicy::AutoDump){
            Ok(db) => db,
            Err(_) => PickleDb::new_json(DB_PATH, PickleDbDumpPolicy::AutoDump)
        }
    }

    pub fn device_in_database(device: &Device) -> bool{
        let db = open_database();

        db.exists(device.mac.as_str())
    }

    pub fn add_device(device: Device) -> Result<(), UnauthorizedDeviceError>{
        let mut db = open_database();

         //TODO check device here and return in case of unathorized access

        db.set(device.mac.as_str(), &[device.devicename, device.ip, device.port]).unwrap();
        Ok(())
    }

    pub mod errors{
        use std::fmt;

        pub struct UnauthorizedDeviceError;

        impl fmt::Debug for UnauthorizedDeviceError{
            fn fmt(&self, f: &mut fmt::Formatter) -> fmt::Result{
                write!(f, "Authentication failed. Device is not allowed to connect to this server")
            }
        }

        impl fmt::Display for UnauthorizedDeviceError{
            fn fmt(&self, f: &mut fmt::Formatter) -> fmt::Result{
                write!(f, "Authentication failed. Device is not allowed to connect to this serve")
            }
        }
    }
}

pub mod errors{
    use std::fmt;

    pub struct ParseError;

    impl fmt::Debug for ParseError{
        fn fmt(&self, f: &mut fmt::Formatter) -> fmt::Result{
            write!(f, "Mac Address parser error: Wasn't able to extract MAC address. A MAC address has to be in the format: xx::xx::xx::xx:xx::xx")
        }
    }
    impl fmt::Display for ParseError{
        fn fmt(&self, f: &mut fmt::Formatter) -> fmt::Result{
            write!(f, "Mac Address parser error: Wasn't able to extract MAC address. A MAC address has to be in the format: xx::xx::xx::xx:xx::xx")
        }
    }
}