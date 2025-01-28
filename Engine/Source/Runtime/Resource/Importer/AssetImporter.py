import hashlib
import json
from pathlib import Path

# Indent affect the reading and writing speed
INDENT = 4
# resource folder
assetResourceFolder = Path(__file__).resolve().parent.parent.parent.parent.parent / "Resource"
# GUID list path
linkPath = assetResourceFolder / "GUIDLists.json"
# The asset type that are supported
assetTypeMap = {
    ".png":"Texture",
    ".jpg":"Texture",
    ".jpeg":"Texture"
}

# respective asset type importation
def LoadTexture(source, data):
    from PIL import Image
    image = Image.open(source)
    data["Width"] = image.width
    data["Height"] = image.height
    data["Channels"] = image.mode
    image = image.convert("RGBA")
    r, g, b, a = image.split()
    r, g, b, a = [list(i.getdata()) for i in (r, g, b, a)]
    match image.mode:
        case "RGB":
            data["Pixels"] = [j for i in zip(r, g, b) for j in i]
        case "RGBA":
            data["Pixels"] = [j for i in zip(r, g, b, a) for j in i]
        case "L":
            data["Pixels"] = [i for i in r]
        case "LA":
            data["Pixels"] = [j for i in zip(r, a) for j in i]
def LoadSound(source, data):
    pass


def main():

    print("This tool convert a given asset source into a target asset used in the engine.")
    print(f"The resource folder is {assetResourceFolder}")

    # Input the asset source and verify the type
    assetSourceAbsolutePath = Path("Hello World!")
    assetType = ""
    while True:
        assetSourceAbsolutePath = Path(input("Input the asset source in absolute path: "))
        if not assetSourceAbsolutePath.exists():
            print("The asset source does not exist.")
            continue
        if not assetSourceAbsolutePath.is_file():
            print("The asset source is not a file.")
            continue
        assetSourceSuffix = assetSourceAbsolutePath.suffix
        if (assetSourceSuffix not in assetTypeMap):
            print("The asset type is not supported.")
            continue
        assetType = assetTypeMap[assetSourceSuffix]
        break

    # Input the asset destination
    assetDestinationRelativePath = Path("Goodbye World!")
    while True:
        assetDestinationRelativePath = Path(input("Input the asset destination in relative path: "))
        if not (assetResourceFolder / assetDestinationRelativePath).parent.exists():
            print("The asset destination folder do not exist.")
            continue
        assetDestinationSuffix = assetDestinationRelativePath.suffix
        if (assetDestinationSuffix != ".json"):
            print("The asset destination is not an .json file.")
            continue
        break
    
    # Perform the asset importation
    print(f"Perform {assetType} importation from {assetSourceAbsolutePath} to {assetResourceFolder / assetDestinationRelativePath}.")
    data = {}
    data["GUID"] = hashlib.sha1(open(assetSourceAbsolutePath, "rb").read()).hexdigest()
    data["Type"] = assetType
    data["Data"] = {}
    match assetType:
        # Load the asset from data, any additional asset type can be ADDED here
        case "Texture":
            LoadTexture(assetResourceFolder / assetSourceAbsolutePath, data["Data"])
            
    json.dump(data, open(assetResourceFolder / assetDestinationRelativePath, "w"), indent = INDENT)
    
    # Save GUID into the list
    print(f"Save the GUID data into {linkPath}.")
    if (linkPath.exists()):
        link = json.load(open(linkPath, "r"))
    else:
        link = {"Data": {}}
    link["Data"][data["GUID"]] = str(assetDestinationRelativePath)
    json.dump(link, open(linkPath, "w"), indent = INDENT)
    
    print("The asset importation is done.")


if __name__ == "__main__":
    main()