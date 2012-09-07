 Introduction
 ------------
 This package contains a shell for neural networks real applications;it isn't
 a demonstration software, it was used for artificial life studies.
 NRLIB is a software library for multiple neural networks management.
 In addition, an interactive program (NREBP) for create,load,compute and 
 train nets with EBP rule is provided.
 NRLIB32  and NREBP32 are shareware programs. You can use them to  test  and
 verify  their  functionality or for private or research use. For commercial 
 or company use register you using the form in last page of this file.
 This  software  was  developped  in C language  and  is  available  for  any
 computer (already used on R6000 and VAX ); but in this package is provided 
 compiled version only for 286/486 PC systems.

 This library provide 50 functions for manage multiple neural networks in C
 programs. You mast include NRLIB32.H file in your program and link it with 
 NRLIB32.OBJ file to use these functions. 
 You can :
  - Create in memory one or more nets (different too).
  - Save and load all nets on/from a file
  - Net compute (input propagate)
  - Net train with EBP (Error Back Propagation)
  or many other manipulations.
 
 Each net can have any number of layers (to 100 layers).
 Each layer can have any number of nodes.
 Each node can have any number of links with others nodes.
 
 The nodes have progressive number in a net.
 You can choose a different activation function for each node.
 There are 9 types of activation function: 5 defined and 4 for user definition.
 For each node it's also possible to define another function named action,
 which is called after the activation function.
 
 Range of principals values:
 - Net number      1 -- 1000 (in this release)
 - Layer number    0 -- 99
 - Node number     1 -- 7FFFFFFF (in hex)
 Memory is dinamically allocated to according nets dimension and availability.
 
 Files included in the package:
 
 - README.TXT   Abstract and orders details
 - NRLIB32.H    Include file for library use  . Functions are described
                like in a manual.
 - NRLIB32.C    Library source
 - NRLIB32.OBJ  Object file that you must link with your program (286 or better
                and math. copr.) (large memory model)
 - NREBP32.C    Complete program (interactive) for EBP net use
 - NREBP32.EXE    (compiled)
 - EXAMPLE1.C   Example of NRLIB31 use (imitation metaphore)
 - EXAMPLE2.C   Example of NRLIB31 use (genetic algoritm)
 - EXAMPLE1/2.EXE (compiled)
 - NRLIB32.PS   Nrlib description in  postscript
 - NRLIB32.TXT     "            in ASCII format (without figures)
 - NETTRAIN.DAT Trainer file for XOR task
 - NNETSINP.DAT Example of nets save file
 - NNETXOR.DAT  Example of nets save file (trained on XOR task)
 
 Version 4 enhancements
 ----------------------
 This  version is already available ;  for any request contact  me .
 Functions available increase to 59.
 More complex logic structure is definable for a net.
 With  simple routines like "createnet", "compute", "learn" etc.  ,  we  can
 manage net with memory contest layer or recursive layer.
 
 Each  layer   can  be  linked with more layers  (to  10)  ,  no  more  with
 following layer only.
 Each layer can have a pointer to a layer  that realize a memory contest.
 Each layer can have a pointer to a layer that realize a duplicated layer.
 
 Before starting compute phase , library routine, copies nodes status  of  a
 layer to input buffer of  the contest memory layer correspondent.
 For  layer duplicated , compute routine , copies nodes status of  the layer
 to the nodes status of  layer duplicated at the same time when compute it.
 
 
 NREBP program
 -------------
 NREBP  program  is included in the package. This program is an  interactive
 software that allows us to create or load one or more nets and activate  or
 train them.
 
 It has 3 way of using :
 - like a filter
 - interactive nets management
 - batch train
 
 For more details ask help typing :  NREBP32   /h

 Address
 -------
 For registration or any question contact me at

 Daniele Denaro
 Via Sergio Forti, 47
 00144 ROMA (ITALY)
 Tel. 39-6-5292189 

 Internet address:
 Mail: daniele@caio.irmkant.rm.cnr.it
 ftp anonymous : kant.irmkant.rm.cnr.it   pub/source/nrlib

                                
LICENSE REGISTRATION

1. Registration object.
   Registration is related to software library for neural networks management
   (and EBP companion program) in compiled object form for MS-DOS , and in
   C source form for any computers.

2. License grant.
   Registration grants to you  a right to use this software in a single copy
   on a single computer, to develop your software neural network  based (or
   for direct use of EBP companion program) for any use. 
   You can include this library in your programs without royaltyes.

3. Warranty.
   Author warrants that the software will perform substantially in accordance
   with the accompanying written materials. 
   Author does not warrant that the software is error free.
   No liability for any use.

4. Copyright.
   The software is protected by international treaty provisions. 
   You acknowledge that no title to the intellectual property in the software
   is transferred to you.

         SOFTWARE                                COPIES         AMOUNT


   Version 3.2  C source ($10 per copy)          __________    $_____________
   (required only for commercial use)

   Version 4.1  C source ($30 per copy)          __________    $_____________
   
                                                     TOTAL     $_____________

   Name:_______________________________________________
   
   Address:____________________________________________

   City/State/Province:________________________________

   Postal Code/Country:________________________________

   Telephone(voice/fax/modem):_________________________

   Signature:__________________________________________                      

