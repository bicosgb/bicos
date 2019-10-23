#!/bin/sh

TOPDIR=${TOPDIR:-$(git rev-parse --show-toplevel)}
SRCDIR=${SRCDIR:-$TOPDIR/src}
MANDIR=${MANDIR:-$TOPDIR/doc/man}

BICOSCOIND=${BICOSCOIND:-$SRCDIR/bicoscoind}
BICOSCOINCLI=${BICOSCOINCLI:-$SRCDIR/bicoscoin-cli}
BICOSCOINTX=${BICOSCOINTX:-$SRCDIR/bicoscoin-tx}
BICOSCOINQT=${BICOSCOINQT:-$SRCDIR/qt/bicoscoin-qt}

[ ! -x $BICOSCOIND ] && echo "$BICOSCOIND not found or not executable." && exit 1

# The autodetected version git tag can screw up manpage output a little bit
BTCVER=($($BICOSCOINCLI --version | head -n1 | awk -F'[ -]' '{ print $6, $7 }'))

# Create a footer file with copyright content.
# This gets autodetected fine for bicoscoind if --version-string is not set,
# but has different outcomes for bicoscoin-qt and bicoscoin-cli.
echo "[COPYRIGHT]" > footer.h2m
$BICOSCOIND --version | sed -n '1!p' >> footer.h2m

for cmd in $BICOSCOIND $BICOSCOINCLI $BICOSCOINTX $BICOSCOINQT; do
  cmdname="${cmd##*/}"
  help2man -N --version-string=${BTCVER[0]} --include=footer.h2m -o ${MANDIR}/${cmdname}.1 ${cmd}
  sed -i "s/\\\-${BTCVER[1]}//g" ${MANDIR}/${cmdname}.1
done

rm -f footer.h2m
