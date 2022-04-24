# AdvancedPhonebookSystem
Aim : To consolidate concepts of DSA, especially Trie, including implementing Terminal based GUI. 

## Motivation :
I was intrigued by how the contacts app in the smartphones that we use everyday actually works. My curiosity to find out more about this made me dig more about this and this inspired me to do a project, so as I can quench my thirst as well consolidate my concepts of Data Structures and Algorithms I was learning as part of a course I have taken.

## Functionalities : 
-Just like how when we talk in the real world, we might want to save somebody's contact details. But I also wanted to make sure of my contacts to not be accessible just by any random stranger, hence I tried to make sure that my phonebook app is secure and hence included an Account-type interface, i.e., a particular account can have an independent phonebook directory of its own which can be accessed only with the right combinations of password and username.

-The user can login into an existing account, or create one if he/she wishes to. 

-He can add contacts, which includes the name, the phone number and the email.

-Now think about if you forgot how you saved your contact, you can't remember the right spelling, you would want your app to be smart enough to suggest you with names right? That is what I have tried to implement here as well, an auto-suggesting feature.

-A delete and edit feature if you have made mistakes in storing the contact, I have also tried to implement checking of valid phone numbers and emails through regex matching.

-The user can view the most frequently contacted contacts, this is to mimic how Speed Dial actually works in our smartphones. The logic is based on which contacts you have accessed the most number of times.

-Also implemented colouring of various aspects of terminal display using ANSI escape characters, including concepts from threading to initialise real world-like interface and waiting intervals.

## Data Structures Used :
- Trie 
- Hash maps
- vectors and other auxiliary data structures

## Language used : C++


