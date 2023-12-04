# VideoGraphDOS-TestTask

## Compile and Launch

Debain(Ubuntu): 

  sudo apt update
  
  sudo apt-get install libpng-dev -y && sudo apt-get install zlib1g-dev -y

  sudo apt install gcc  

  gcc MAIN.C FILEOPS.C DECODER.C VIDMODE.C -lpng

  (to link libpng package `-lpng` is used)
