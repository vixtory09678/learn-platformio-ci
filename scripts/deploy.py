import firebase_admin
from firebase_admin import credentials, storage, db
import os
import sys
from uuid import uuid4
from dotenv import load_dotenv

load_dotenv()

if len(sys.argv) < 2:
    exit("please input your firmware version")

firmware_version = sys.argv[1]

if firmware_version.startswith("v") == False:
    exit("firmware version must start with v")

firebaseEnv = os.getenv("FIREBASE_CREDENTIAL")

print(len(firebaseEnv))

if firebaseEnv is not None:
    f = open("serviceAccountKey.json", "w")
    f.write(firebaseEnv)
    f.close()
else:
    exit("FIREBASE_CREDENTIAL does't exits, please check your environment")

cred = credentials.Certificate("serviceAccountKey.json")
firebase_admin.initialize_app(
    cred,
    {
        "storageBucket": "iamteam-playground.appspot.com",  # set your storage bucket with out gs:// prefix
        "databaseURL": "https://iamteam-playground-default-rtdb.asia-southeast1.firebasedatabase.app/",  # set your databaseURL
    },
)

# get firmware binary file
fileName = ".pio/build/esp32dev/firmware.bin"

uuid = uuid4()

bucket = storage.bucket()
blob = bucket.blob("firmware/{firmware_name}.bin".format(firmware_name=uuid))
blob.upload_from_filename(fileName)

blob.make_public()

db.reference("/firmware/{key}".format(key=uuid)).set(
    {
        "id": "" + str(uuid),
        "firmwareUrl": blob.public_url,
        "firmwareVersion": firmware_version,
        "firmwareName": "learn-platformio-ci",
    }
)
