import json

def json_output(gadget_list, file):
    json_list = []
    for gadgets in gadget_list:
        json_list.append(gadgets.to_dict())

    json_str = json.dumps(json_list, indent=4)
    file_name = file + ".json"
    with open(file_name, "w") as f:
        f.write(json_str)

def display_output(output_json, gadget_list, scanner):
    if (output_json):
        json_output(gadget_list, output_json)
    else:
        scanner.print_gadgets(gadget_list)