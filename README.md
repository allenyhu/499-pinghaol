Pinghao Luo pinghaol
    @usc.edu

#How to setup and compile ?
        make

#How to run ?

#keyValue:
            ./
    keyValueServer

#serviceServer:
        ./
    serviceServer

#serviceClient:

#command:
        ./
    command-- register username1

#chirp without parent:
        ./
    command-- user username1-- chirp "chirp1"

    Return a message : Success,
    and chirp id is : chirp_id

#chirp witht ParentID:
                          ./
        command-- user username1-- chirp "chirp1" --reply chirp_id

            Return a message : Success,
    and chirp id is : chirp_id

#read:
                          ./
        command-- read chirp_id

            Return a message : Reading chirps posted by username1 : chirp1

#follow:
                                                                        ./
        command-- user username1-- follow username2

#monitor:
            ./
        command-- user username1-- monitor
