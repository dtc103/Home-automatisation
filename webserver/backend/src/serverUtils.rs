use std::fmt;
use std::net::{TcpListener, TcpStream, ToSocketAddrs};
use std::io::prelude::*;
use pickledb::{PickleDb, PickleDbDumpPolicy};
use regex::Regex;

pub struct MACAddress{
    address: String,
}

impl MACAddress{    
    pub fn new(mac: String) -> Result<Option<MACAddress>, MacParseError>{
        match Self::check_mac(&mac){
            Ok(is_database) => {
                if is_database{
                    return Ok(Some(MACAddress{address: mac}))
                }else{
                    return Ok(None)
                }
            }
            Err(e) => Err(e)
        }
    }

    //first checks if the mac address is in the correct format
    //then returns if the mac address is already in the database
    fn check_mac(mac_address: &String) -> Result<bool, MacParseError>{
        let mac_regex = Regex::new(r"^([0-9a-fA-F]{2}::){5}[0-9a-fA-F]{2}$").unwrap();
        if !mac_regex.is_match(mac_address){
            return Err(MacParseError);
        }

        let db_path = "mac.db";

        let db = match PickleDb::load_json(db_path, PickleDbDumpPolicy::NeverDump){
            Ok(db) => db,
            Err(_) => PickleDb::new_json(db_path, PickleDbDumpPolicy::NeverDump)
        };

        Ok(db.exists(mac_address.as_str()))
    }
}

pub struct MacParseError;

impl fmt::Debug for MacParseError{
    fn fmt(&self, f: &mut fmt::Formatter) -> fmt::Result{
        write!(f, "Mac Address parser error: Wasn't able to extract MAC address. A MAC address has to be in the format: xx::xx::xx::xx:xx::xx")
    }
}
impl fmt::Display for MacParseError{
    fn fmt(&self, f: &mut fmt::Formatter) -> fmt::Result{
        write!(f, "Mac Address parser error: Wasn't able to extract MAC address. A MAC address has to be in the format: xx::xx::xx::xx:xx::xx")
    }
}