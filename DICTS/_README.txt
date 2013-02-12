
All dictionaries must be in RAW BINARY format,
and MUST use the following naming convention:


The names themselves can be anything you want,
but the 3-character filename extension MUST be
in the following format:


        <filename>.FST


Where:
  
    F     Dictionary Format    0/1
    S     Symbol Size          1-5
    T     Dictionary Type      C/E



Thus, for a 13-bit CDSS format-1 dictionary
there must be TWO files with whatever name
you want, but with filename extensions of:


      .15C      Compression dictionary
      .15E      Expansion dictonary



For example:


    mydict.03C
    mydict.03E
    foobar.15C
    foobar.15E
    ...etc...


Both dictionaries must of course have the
same name (duh!), and as mentioned must be
in raw binary format.
