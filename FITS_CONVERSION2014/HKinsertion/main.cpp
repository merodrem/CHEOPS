/******************************************************************************
 * main.cpp
 *
 * First draft of test to merge HK data with FITS files. To be included to a
 * future Qt application.
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License version 3
 * as published by the Free Software Foundation; or, when distributed
 * separately from the Linux kernel or incorporated into other
 * software packages, subject to the following license:
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this source file (the "Software"), to deal in the Software without
 * restriction, including without limitation the rights to use, copy, modify,
 * merge, publish, distribute, sublicense, and/or sell copies of the Software,
 * and to permit persons to whom the Software is furnished to do so, subject to
 * the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS
 * IN THE SOFTWARE.
 *
 * Author: Julien Graisse <julien.graisse@epfl.ch> for the Swiss Space Center
 */


#include <QFile>
#include <QApplication>
#include <QListIterator>

#include <iostream>


#include <CCfits/CCfits>
#include <cmath>


#define NUMBER_PARAMS 19
#define NUMBER_STARS 100
#define IMAGES_PER_FILE 60

using namespace CCfits;
using namespace std;
using std::valarray;

const QString COL_NAMES[NUMBER_PARAMS] = {"TOTAL TIME SEC", "FU", "FB", "FV", "FR",
                                          "FI", "ORBIT_ANGLE", "STRAY_B", "STRAY_V",
                                          "STRAY_R", "STRAY_I", "STA_VAR f", "PLA_TR",
                                          "STAR NO", "POS X", "POS Y", "dx(wiggle)",
                                          "dy(wiggle)", "dark_f"};

void  merge(const QString &directory,const QString &dataFile);
vector<string> convertRawData(const QList<QByteArray> &data);

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    QStringList cmdline_args = QCoreApplication::arguments();
    merge(cmdline_args[1], cmdline_args[2]);

    return 0;
}


vector<string> convertRawData( const QList<QByteArray>& data)
{
    vector<string> result(0);
    QListIterator<QByteArray> it(data);
    while (it.hasNext())
    {
        double nextElem = it.next().toDouble();
#ifdef SSTREAM_DEFECT
        std::ostrstream pStr;
#else
        std::ostringstream pStr;
#endif
    pStr << nextElem ;
#ifdef SSTREAM_DEFECT
    pStr << std::ends;
#endif
    result.push_back(string(pStr.str()));
    }
    return result;
}

void  merge(const QString &directory, const QString &dataFile){
    QFile HK(dataFile);


    HK.open(QIODevice::ReadOnly);


    HK.readLine(2048);//Parameters line, could be used instead of hard-coding them

    int file_counter(0);

    //loop on all the HK(time) file
    while (!HK.atEnd())
    {


#ifdef SSTREAM_DEFECT
         std::ostrstream pStr;
#else
         std::ostringstream pStr;
#endif
         pStr << file_counter ;
#ifdef SSTREAM_DEFECT
          pStr << std::ends;
#endif


        //Beware to this simplification: the code will only work if the files are of the form SimDataX.fits
        const std::string fileName(directory.toStdString() +"SimData" + string(pStr.str())+".fits");
        FITS currentFITS(fileName, Write);


        unsigned int rows(NUMBER_STARS);
        for (int j = 0 ; j < IMAGES_PER_FILE && !HK.atEnd() ; ++j)
            {

#ifdef SSTREAM_DEFECT
             std::ostrstream pStr;
#else
             std::ostringstream pStr;
#endif
             pStr << j+1 ;
#ifdef SSTREAM_DEFECT
              pStr << std::ends;
#endif
            string hduName("IMAGE" + string(pStr.str()));
            std::vector<string> colName(NUMBER_PARAMS,"");
            std::vector<string> colForm(NUMBER_PARAMS,"8A");
            std::vector<string> colUnit(NUMBER_PARAMS,"");

            for(int i = 0 ; i < NUMBER_PARAMS ; ++i)
            {
                colName[i] = COL_NAMES[i].toStdString();
            }

            Table* newTable = currentFITS.addTable(hduName,rows,colName,colForm,colUnit);

            //ccfits tables work by columns, not by rows
            vector<vector<string> > data(NUMBER_PARAMS);

            vector<string> defaultVector(0);

            //initialization of the columns
            for (int i = 0 ; i < NUMBER_PARAMS ; ++i)
            {
                data[i] = defaultVector;
            }


            for (int i = 0 ; i < NUMBER_STARS ; ++i){
                QList<QByteArray>line = HK.readLine(2048).split(' ');
                line.removeAll("");//TODO: use regexp
                line.removeAll("\n");

                vector<string> formattedLine = convertRawData(line);

                for (int i = 0 ; i < formattedLine.size() ; ++i)
                {
                    data[i].push_back(formattedLine[i]);
                }
            }
            for (int i = 0 ; i < NUMBER_PARAMS ; ++i)
            {
                try{
                    newTable->column(colName[i]).write(data[i],1);
                }
                catch(FitsError e){
                  //  cout << "This table already exists!" <<endl;
                }
            }
        }
        cout << "file " << file_counter << " overwritten!"<<endl;
        file_counter++;
    }


    HK.close();
}
