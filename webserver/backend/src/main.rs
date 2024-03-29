#[macro_use] extern crate rocket;

use regex::Regex;

use std::path::{Path, PathBuf};

use rocket::Request;
use rocket::response::Response;
use rocket::http::Status;
use rocket::serde::{json::Json, Serialize, Deserialize};

use rocket::fs::NamedFile;
use rocket::fs::{FileServer, Options};

mod server_utils;
use server_utils::Device;
use server_utils::database;

#[launch]
fn rocket() -> _ {
    rocket::build()
        //.mount("/", routes![index, indexfiles])
        .mount("/", FileServer::from("../websites/index"))
        .mount("/devices/panel", FileServer::from("../websites/devices/panel").rank(-1))
        .mount("/authenticate", routes![authenticate])
        .mount("/commands", routes![command])
        
}

/**
 * Authenticates new devices, which want to connect
 */
#[post("/", format="application/json", data="<device>")]
async fn authenticate(device: Json<Device>) -> Status{
    let dev = match Device::new(device.devicename.clone(), device.mac.clone(), device.ip.clone(), device.port.clone()){
        Ok(d) => d,
        Err(err) => {
            println!("{}", err);
            return Status::BadRequest;
        }, 
    };

    if !database::device_in_database(&dev){
        if let Ok(_) = database::add_device(dev){
            return Status::Accepted
        }else{
            return Status::Forbidden;
        }
    }

    return Status::Accepted;
}

#[get("/<device>/<command>")]
async fn command(device: &str, command: &str) -> String{
    format!("device: {}, command: {}", device, command)
}

