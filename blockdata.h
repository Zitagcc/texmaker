/***************************************************************************
 *   copyright       : (C) 2003-2011 by Pascal Brachet                     *
 *   http://www.xm1math.net/texmaker/                                      *
 *   addons by Luis Silvestre                                              *
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 ***************************************************************************/

#ifndef BLOCKDATA_H
#define BLOCKDATA_H

#include <QTextBlock>
#include <QTextBlockUserData>

struct ParenthesisInfo {
	QChar character;
	int position;
};

typedef ParenthesisInfo LatexBlockInfo;

class BlockData : public QTextBlockUserData
{
public:
    BlockData() {}
    ~BlockData();
    static BlockData *data(const QTextBlock &block) { return static_cast<BlockData *>(block.userData()); }
    QList<int> code;
    QList<bool> misspelled;
    const QVector<ParenthesisInfo *>& parentheses();
    const QVector<LatexBlockInfo *>& latexblocks();

    /**
     * @brief insertPar
     * @param info
     * @warning this will take ownership of the pointer
     */
    void insertPar( ParenthesisInfo *info );

    /**
     * @brief insertLat
     * @param info
     * @warning this will take ownership of the pointer
     */
    void insertLat( LatexBlockInfo *info );
private:
    template <typename T>
    void insertType(QVector<T*>& vec, T* info);

	QVector<ParenthesisInfo *> m_parentheses;
	QVector<LatexBlockInfo *> m_latexblocks;
};

#endif
