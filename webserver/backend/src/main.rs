#[macro_use] extern crate rocket;
use rocket::serde::{Deserialize};

use pickledb::{PickleDb, PickleDbDumpPolicy};

use regex::Regex;

use rocket::http::{Status, ContentType};
use rocket::response::{status, content};
use rocket::serde::{json::Json, Serialize};

use rocket::fs::{NamedFile, FileServer};

mod serverUtils;
use serverUtils::MACAddress;

#[launch]
fn rocket() -> _ {
    rocket::build()
        .mount("/", routes![index, json])
        .mount("/hello", routes![])

}

#[post("/authentication", format = "application/json", data = "<mac>")]
fn authentication(mac: String) -> Status{
    match MACAddress::new(mac){
        Ok(smac) => {

            Status::Accepted
        },
        Err(e) => {
            Status::BadRequest
        }
    }
}

#[get("/")]
async fn index() -> Option<NamedFile>{
    NamedFile::open("./../../website/index.html").await.ok()
}

#[get("/todo")]
fn json() -> Json<TestForJSON>{
    Json(TestForJSON{
        elem1: 14,
        elem2: 5,
        elem3: "frick"
    })
}

#[derive(Serialize)]
struct TestForJSON{
    elem1 : i32,
    elem2 : i32,
    elem3 : &'static str,
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