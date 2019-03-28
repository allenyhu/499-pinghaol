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
     ./serviceClient --register username1
            
            
# chirp without parent:
    ./serviceClient --user username1 --chirp chirp1

    Return a message: Success, and chirp id is: chirp_id

# chirp witht ParentID:
    ./serviceClient --user username1 --chirp chirp1 --reply chirp_id

    Return a message: Success, and chirp id is: chirp_id

# read:
    ./serviceClient --read chirp_id
    
    Return a message:
        Reading chirps posted by username1:
            chirp1

# follow:
    ./serviceClient --user username1 --follow username2

# monitor:
    ./serviceClient --user username1 --monitor
        


