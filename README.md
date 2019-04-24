Pinghao Luo pinghaol@usc.edu

#How to setup and compile ? make

#How to run ?

#keyValue: ./keyValueServer

#serviceServer: ./serviceServer

#serviceClient:

#command: ./command-- register username1

#chirp without parent: ./command-- user username1-- chirp "chirp1"
    Return a message : Success, and chirp id is : chirp_id

#chirp with ParentID: ./command-- user username1-- chirp "chirp1" --reply chirp_id
    Return a message : Success, and chirp id is : chirp_id

#read: ./command-- read chirp_id
    Return a message : Reading chirps posted by username1 : chirp1

#follow: ./command-- user username1-- follow username2

#monitor: ./command-- user username1-- monitor

#stream: ./command --user <username> --stream <tag>
    tag must be enclosed in " " and include the #
    Ex: "#tag" is valid but "tag" is not
    When chirping will only parse hashtag if there is leading whitespace (<text> <tag>), but will accept a chirp with only tag as text
