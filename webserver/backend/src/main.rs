#[macro_use] extern crate rocket;
use rocket::serde::{Deserialize};
use serde::

use pickledb::{PickleDb, PickleDbDumpPolicy};

use regex::Regex;

#[derive(Deserialize)]
struct MACAddress<'r>{
    address: &'r str,
}


#[launch]
fn rocket() -> _ {
    rocket::build()
        .mount("/", routes![index])
        .mount("/hello", routes![])
}

#[get("/")]
fn index() -> &'static str{
    "Hello World"
}
/*
#[post("/users", format="application/json", data="<user>")]
fn world(user: Json) -> &'static str{
    "yes yes"
}
*/
fn check_mac(mac_address: String) -> bool{
    let mac_regex = Regex::new(r"^([0-9a-fA-F]{2}::){5}[0-9a-fA-F]{2}$").unwrap();
    if !mac_regex.is_match(mac_address.as_str()){
    }

    let db_path = "mac.db";

    let db = match PickleDb::load_json(db_path, PickleDbDumpPolicy::NeverDump){
        Ok(db) => db,
        Err(e) => PickleDb::new_json(db_path, PickleDbDumpPolicy::NeverDump)
    };

    db.exists(mac_address.as_str())
}