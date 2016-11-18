--NEWGEN-START 84
sentence = formatted:string + unformatted:unformatted;
text = sentences:sentence*;
unformatted = label:string x number:int x extra_margin:int x words:string*;
