Pinghao Luo
pinghaol@usc.edu


# How to setup and compile?
    make
    
    
# How to run?

# keyValue: 
    ./keyValueServer

# serviceServer:
    ./serviceServer 

# serviceClient:

# register:
     ./serviceClient --register test_user
            
            
# chirp without parent:
    ./serviceClient --user username --chirp chirp_text 

    Return a message: Success, and chirp id is: test_chirp

# chirp witht ParentID:
    ./serviceClient --user username --chirp chirp_text --reply test_chirp

    Return a message: Success, and chirp id is: test_chirp

# read:
    ./serviceClient --read chirp_id
    
    Return a message:
        Reading chirps posted by test_user:
            chirptext

# follow:
    ./serviceClient --user test_user --follow test_user1

# monitor:
    ./serviceClient --user test_user --monitor
        


