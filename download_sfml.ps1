$wc = New-Object System.Net.WebClient
Add-Type -AssemblyName System.IO.Compression.FileSystem

# Download 32 bit SFML
$url = "https://www.sfml-dev.org/files/SFML-2.5.1-windows-vc15-32-bit.zip"
$outpath = "sfml_Win32"
$zipfile = "$outpath.zip"

if (Test-Path $outpath) {
    echo "$outpath exists already. Skipping."
} else {
    echo "Downloading $zipfile..."
    $wc.DownloadFile($url, $zipfile)
    echo "Extracting $zipfile..."
    [System.IO.Compression.ZipFile]::ExtractToDirectory($zipfile, ".")
    Rename-Item -Path "SFML-2.5.1" -NewName $outpath
    Remove-Item $zipfile
}

# Download 64 bit SFML
$url = "https://www.sfml-dev.org/files/SFML-2.5.1-windows-vc15-64-bit.zip"
$outpath = "sfml_x64"
$zipfile = "$outpath.zip"

if (Test-Path $outpath) {
    echo "$outpath exists already. Skipping."
} else {
    echo "Downloading $zipfile..."
    $wc.DownloadFile($url, $zipfile)
    echo "Extracting $zipfile..."
    [System.IO.Compression.ZipFile]::ExtractToDirectory($zipfile, ".")
    Rename-Item -Path "SFML-2.5.1" -NewName $outpath
    Remove-Item $zipfile
}