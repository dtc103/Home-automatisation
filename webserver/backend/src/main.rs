#[macro_use] extern crate rocket;

use regex::Regex;

use std::path::{Path, PathBuf};

use rocket::Request;
use rocket::response::Response;
use rocket::http::Status;
use rocket::serde::{json::Json, Serialize, Deserialize};

use rocket::fs::NamedFile;
use rocket::fs::FileServer;

mod server_utils;
use server_utils::Device;
use server_utils::database;

#[launch]
fn rocket() -> _ {
    rocket::build()
        .mount("/", routes![index, indexfiles])
        .mount("/authenticate", routes![authenticate])
        .mount("/devices", routes![devicepath])
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


#[get("/")]
async fn index() -> Option<NamedFile>{
    NamedFile::open("../websites/index/index.html").await.ok()
}

//this function is for returning all the corresponding javascript and css files
#[get("/<file..>")]
async fn indexfiles(file: PathBuf) -> Option<NamedFile>{
    NamedFile::open(Path::new("../websites/index").join(file)).await.ok()
}

#[get("/<device>")]
async fn devicepath(device: &str) -> Option<NamedFile>{
    NamedFile::open(Path::new("../websites/devices").join(device)).await.ok()
}