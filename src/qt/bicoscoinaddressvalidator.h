// Copyright (c) 2011-2014 The BICOScoin Core developers
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#ifndef BICOSCOIN_QT_BICOSCOINADDRESSVALIDATOR_H
#define BICOSCOIN_QT_BICOSCOINADDRESSVALIDATOR_H

#include <QValidator>

/** Base58 entry widget validator, checks for valid characters and
 * removes some whitespace.
 */
class BICOScoinAddressEntryValidator : public QValidator
{
    Q_OBJECT

public:
    explicit BICOScoinAddressEntryValidator(QObject *parent);

    State validate(QString &input, int &pos) const;
};

/** BICOScoin address widget validator, checks for a valid bicoscoin address.
 */
class BICOScoinAddressCheckValidator : public QValidator
{
    Q_OBJECT

public:
    explicit BICOScoinAddressCheckValidator(QObject *parent);

    State validate(QString &input, int &pos) const;
};

#endif // BICOSCOIN_QT_BICOSCOINADDRESSVALIDATOR_H
