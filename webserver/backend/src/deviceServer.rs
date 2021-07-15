use std::fmt;
use std::net::{TcpListener, TcpStream, ToSocketAddrs};
use std::io::prelude::*;
use pickledb::{PickleDb, PickleDbDumpPolicy};
use regex::Regex;


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

pub struct DeviceServer{
    pub listener: TcpListener,
}

impl DeviceServer{
    pub fn new<A>(addr: A) -> Self where A:ToSocketAddrs{
        DeviceServer{
            listener: TcpListener::bind(addr).expect("Failed while creating socket"),
        }
    }

    pub fn start_server(&self){
        for stream in self.listener.incoming(){
            let stream = stream.unwrap();
            std::thread::spawn(|| {
                Self::handle_connection(stream);
            });
        }
    }

    fn handle_connection(mut stream: TcpStream){
        
    }

    fn check_mac(mac_address: String) -> Result<bool, MacParseError>{
        let mac_regex = Regex::new(r"^([0-9a-fA-F]{2}::){5}[0-9a-fA-F]{2}$").unwrap();
        if !mac_regex.is_match(mac_address.as_str()){
            return Err(MacParseError);
        }

        let db_path = "mac.db";

        let db = match PickleDb::load_json(db_path, PickleDbDumpPolicy::NeverDump){
            Ok(db) => db,
            Err(e) => PickleDb::new_json(db_path, PickleDbDumpPolicy::NeverDump)
        };

        Ok(db.exists(mac_address.as_str()))
    }
}