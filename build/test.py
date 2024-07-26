import mstmap

mst = mstmap.MSTmap()

input_file_set = False

while not input_file_set:
    try:
        mst.set_input_file("non_existent_file.txt")
        input_file_set = True
    except RuntimeError as e:
        print(f"Error: {e}")
        # Prompt the user to enter the correct file path
        new_input_file = input("Please enter the correct input file path: ")
        try:
            mst.set_input_file(new_input_file)
            input_file_set = True
        except RuntimeError as e:
            print(f"Error: {e}")
            # Continue the loop to prompt for input again
            continue

mst.set_output_file("output_file.txt")
mst.run()