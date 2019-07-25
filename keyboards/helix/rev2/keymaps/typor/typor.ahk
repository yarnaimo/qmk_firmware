#Include IME.ahk

#If, IME_GET()
    $q:: send {a}{i}
    $-:: send {o}{u}
    $=:: send {e}{i}
    $c:: send {u}{i}
    $l:: send {u}{u}
