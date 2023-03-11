
:: 7zip Batch Script

@echo off

pushd.

rem ===============================================================================================
rem 7 Zip archive command-line switch
rem 
rem   7z a -v1g "target_out_file_path" "source_file_or_dir"
rem
rem   -v + option : for split volumn size, b, k, m, g (bytes, kilobytes, megabytes, gigabytes)
rem
rem Example
rem   7z a -tzip -v1g ".\out\archive.zip" ".\in\*.*"
rem ===============================================================================================



rem ===============================================================================================
rem 7 Zip extract command-line switch
rem 
rem   7z x -o"target_out_file_path" "source_file_or_dir"
rem
rem   -o + option : for out path
rem
rem Example
rem   7z x -o".\out\" ".\in\*.zip.001" -r -y (first part of zip file)
rem ===============================================================================================

popd.

pause