#! /bin/bash

# BPS Main script: batch handling of S BANK

# Check if the number of arguments is correct
#if [ "$#" -ne 1 ]; then
#    echo "Error: Please provide a file path."
#    exit 1
#fi

lock_dir="/home/parallels/Documents/project"
bk_dir="/home/parallels/Documents/project/bankdata"

echo " "
echo "<<<<< S Bank Batch Run Begin >>>>>>"


# check the file from branch whether ready
echo " "
echo "<<<<<< STAGE 0: Check if Data ready >>>>>>"
echo " "
if [ ! -f "/home/parallels/Documents/project/bankdata/b01/transaction" ]; then
  touch "/home/parallels/Documents/project/bankdata/b01/transaction"
fi
if [ ! -f "/home/parallels/Documents/project/bankdata/b02/transaction" ]; then
  touch "/home/parallels/Documents/project/bankdata/b02/transaction"
fi
if [ ! -f "/home/parallels/Documents/project/bankdata/b03/transaction" ]; then
  touch "/home/parallels/Documents/project/bankdata/b03/transaction"
fi

# Data verification
echo " "
echo "<<<<<< STAGE 1: Data Verification >>>>>>"
echo " "
   ./bps001 b01 &
   ./bps001 b02 &
   ./bps001 b03 &
   
# backup before update
cp -r "./bankdata/transaction" "./bankdata/transaction.bk1"

# Data update
sleep 20
echo " "
echo "<<<<<< STAGE 2: Account Update >>>>>>"
echo " "
lock_file="bankdata.lock"
# get file lock
   exec 200>$lock_file
   flock -n 200 || exit 1
   ./bps002 b01 &
   ./bps002 b02 &
   ./bps002 b03 &
# release file lock
   flock -u 200

# backup again after update
cp -r "./bankdata/transaction" "./bankdata/transaction.bk2"

# generate report
sleep 20
echo " "
echo "<<<<<< STAGE 3: Generate Reports >>>>>>"
echo " "
   ./bps003 b01 &
   ./bps003 b02 &
   ./bps003 b03 &
   
sleep 20
echo " "
echo "<<<<<< All batch processing done >>>>>>"


