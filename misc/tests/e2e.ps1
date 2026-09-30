$ErrorActionPreference = "Stop"
$root = Split-Path -Parent (Split-Path -Parent $PSScriptRoot)
$bin = Join-Path $root "exec"
$out = Join-Path $root "build\out"
New-Item -ItemType Directory -Force -Path $out | Out-Null

if (-not $env:JAVA_HOME) {
  $jdk = Get-ChildItem "C:\Program Files\Microsoft\jdk-*" -Directory -ErrorAction SilentlyContinue |
    Select-Object -First 1
  if ($jdk) { $env:JAVA_HOME = $jdk.FullName }
}

$failures = 0
function Check([string]$name, [scriptblock]$fn) {
  try {
    & $fn
    Write-Host "PASS  $name"
  } catch {
    $script:failures++
    Write-Host "FAIL  $name - $($_.Exception.Message)"
  }
}

$jdl34 = Join-Path $bin "jdl34.exe"
if (-not (Test-Path $jdl34)) { Write-Host "build first: cmake --build build"; exit 1 }

Check "probe" {
  & $jdl34 probe | Out-Null
  if ($LASTEXITCODE -ne 0) { throw "probe exit $LASTEXITCODE" }
}

Check "build c" {
  & $jdl34 build --lang c -o "$out\hello-c" (Join-Path $root "share\samples\c\hello.c") | Out-Null
  if ($LASTEXITCODE -ne 0) { throw "build exit $LASTEXITCODE" }
  $r = & "$out\hello-c.exe"
  if ($r -notmatch "hello from C") { throw "bad output: $r" }
}

Check "build cpp" {
  & $jdl34 build --lang cpp -o "$out\hello-cpp" (Join-Path $root "share\samples\cpp\hello.cpp") | Out-Null
  if ($LASTEXITCODE -ne 0) { throw "build exit $LASTEXITCODE" }
  $r = & "$out\hello-cpp.exe"
  if ($r -notmatch "hello from C\+\+") { throw "bad output: $r" }
}

Check "driver incremental" {
  $hv = "$out\hello-drv"
  & $jdl34 driver --lang c -o $hv (Join-Path $root "share\samples\c\hello.c") | Out-Null
  if ($LASTEXITCODE -ne 0) { throw "driver run1 exit $LASTEXITCODE" }
  $r = & "$hv.exe"
  if ($r -notmatch "hello from C") { throw "bad output: $r" }
  $first = & $jdl34 driver --lang c -o $hv (Join-Path $root "share\samples\c\hello.c") 2>&1
  if ($LASTEXITCODE -ne 0) { throw "driver run2 exit $LASTEXITCODE" }
  if ($first -notmatch "up to date") { throw "expected up to date, got: $first" }
}

if ($env:JAVA_HOME) {
  Check "build java (exe)" {
    $prev = $ErrorActionPreference
    $ErrorActionPreference = "Continue"
    & $jdl34 build --lang java --main Hello -o "$out\hello-java" (Join-Path $root "share\samples\java\Hello.java") 2>&1 | Out-Null
    $code = $LASTEXITCODE
    $ErrorActionPreference = $prev
    if ($code -ne 0) { throw "build exit $code" }
    $jx = "$out\hello-java\hello-java.exe"
    if (-not (Test-Path $jx)) { throw "java exe missing at $jx" }
    $r = & $jx
    if ($r -notmatch "hello from Java") { throw "bad output: $r" }
  }
} else {
  Write-Host "SKIP  java (no JAVA_HOME)"
}

if (Get-Command dotnet -ErrorAction SilentlyContinue) {
  Check "build cs" {
    $prev = $ErrorActionPreference
    $ErrorActionPreference = "Continue"
    & $jdl34 build --lang cs -o "$out\hello-cs" (Join-Path $root "share\samples\cs\Program.cs") 2>&1 | Out-Null
    $code = $LASTEXITCODE
    $ErrorActionPreference = $prev
    if ($LASTEXITCODE -ne 0) { throw "build exit $code" }
    if (-not (Test-Path "$out\hello-cs.exe")) { throw "hello-cs.exe missing" }
    $r = & "$out\hello-cs.exe"
    if ($r -notmatch "hello from C#") { throw "bad output: $r" }
  }
} else {
  Write-Host "SKIP  cs (no dotnet toolchain)"
}

if ($failures -eq 0) {
  Write-Host "ALL TESTS PASSED"
} else {
  Write-Host "$failures TESTS FAILED"
  exit 1
}