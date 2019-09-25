
# interactive English dictionary using data.json file attacked to look up a word

import json                                       # import json lib
from difflib import get_close_matches              # import get clost matches for suggestions on words that can be simular to mis typed word
data = json.load(open("data.json"))                 # set varibale data to open and load json dictionary type file think of this as a dict in python
#############################################################################################################
def translate(w):                                   # method used to translate and look up the word
    if w in data:                 # if user input in dictionary then return the definition
        return data[w]

    elif w.title() in data:      # same as above but for capitals such as paris
        return(data[w.title()])
 
    elif w.upper() in data:         # for acronyms such as NATO and USA
        return(data[w.upper()])

    elif len(get_close_matches(w, data.keys())) > 0:             # check if input in any input to begin with then close matches default ratio is .8
        yn = input("Did you mean %s instead? Enter Y if yes, or N if no: " % get_close_matches(w, data.keys())[0])
        if yn == "Y":                                                  # if y return get_close_matches word
            return data[get_close_matches(w, data.keys())[0]]
        elif yn == "N":                                                 # if n return word doesnt exist
            return "The word doesn't exist. Please double check it."
        else:
            return "We didn't understand your entry."
    else:                                                               # outside block for if the user doesn't input anything
        return "The word doesn't exist. Please double check it."
###########################################################################################################
word = input("Enter word: ")                #program starts here
output = translate(word)                   # call translate function with user input as w or argument
if type(output) == list:                   # discriminate as list to print lib without brackets
    for item in output:
        print(item)
else:
    print(output)
