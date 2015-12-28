﻿#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFile>
#include <QTextStream>
#include <QDir>
#include <QMessageBox>
#include <QProcess>
#include <QDebug>
#include <QApplication>
#include <math.h>
#include <degisken.h>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_comboBox_activated(int index)
{
    //ui->label_11->setText("Kelime Uzunluğu "+ ui->comboBox->currentText()+" olarak ayarlandı!");
    karaktersayisi_glob = index;
}

void MainWindow::on_pushButton_clicked()
{

    QMessageBox mesajkutusu;
    QDir yol("/home/");
    QString s;
    int dizi[94];
    int buyukharf[26];
    int kucukharf[26];
    int sayilar[10];
    int ozelkarakterler[33];
    int sayac;
    int l1=0;
    int l2=0;
    int l3=0;
    int l4=0;
    int karaktersayisi=0;
    int progress_sayac=0;
    int x,y,z,t,w,q,m,n,g,h;
    QString on_ek,son_ek,mesajkutusustring,birim,dosyaboyutu_son_string;
    s = yol.relativeFilePath("Wordlyst.list");
    //QString dosya = "Kelime_Listesi";

    // QFile dosyayı oluşturdu.
    QFile file(s);

    //QIODevice::Truncate, Dosyanın içeriğini temizler.
    file.open(QIODevice::ReadWrite | QIODevice::Truncate);

    QTextStream stream(&file);

    on_ek = ui->lineEdit->text();
    son_ek = ui-> lineEdit_2->text();

    /*  Ascii için seçeneklere göre diziyi yapılandırıyoruz.
        Sıralama: Büyük Harf > Küçük harf > Sayılar > Özel karakterler
        Ascii tablosundan decimal olarak değer aralıkları;
        Büyük Harf-> checkbox2 - [65-90]
        Küçük harf-> checkbox - [97-122]
        Sayılar-> checkbox3 - [48-57]
        Özel karakterler(printable)-> checkbox4 - [32-47],[58-64],[91-96],[123-126]
    */



    //Karakterlerin diziye aktarılması
    sayac = 0;
    for(int buyuk=65;buyuk<=90;buyuk++)
    {
        buyukharf[sayac]=buyuk;
        sayac++;
    }
    sayac = 0;
    for(int kucuk=97;kucuk<=122;kucuk++)
    {
        kucukharf[sayac]=kucuk;
        sayac++;
    }
    sayac = 0;
    for(int sayi=48;sayi<=57;sayi++)
    {
        sayilar[sayac]=sayi;
        sayac++;
    }
    sayac = 0;
    for(int ozel=32;ozel<=47;ozel++)
    {
        ozelkarakterler[sayac]=ozel;
        sayac++;
    }
    sayac=16;
    for(int ozel=58;ozel<=64;ozel++)
    {
        ozelkarakterler[sayac]=ozel;
        sayac++;
    }
    sayac = 23;
    for(int ozel=91;ozel<=96;ozel++)
    {
        ozelkarakterler[sayac]=ozel;
        sayac++;
    }
    sayac = 29;
    for(int ozel=123;ozel<=126;ozel++)
    {
        ozelkarakterler[sayac]=ozel;
        sayac++;
    }
    //sayac son değeri = 33 olmalı!
    //Checkbox'ların seçili olup olmadığını kontrol et. Seçim yapılmadıysa açılır pencere ile uyarı ver.
    if(ui->comboBox->currentIndex()==-1)
    {
        QMessageBox::warning(NULL,"Warning","Please select the word length!");
    }
    else
    {
        if(!ui->checkBox->isChecked() && !ui->checkBox_2->isChecked() && !ui->checkBox_3->isChecked() && !ui->checkBox_4->isChecked())
        {
            QMessageBox::warning(NULL,"Warning","You should select at least one of Uppercase, Lowercase, Numbers or \nSpecial Characters to initialize the operation!");
        }
        else
        {

            /*
            //Karakter seti uçbirime yollama
            for(int j=0;j<26;j++)
                qDebug() << QVariant(buyukharf[j]).toChar();
            for(int j=0;j<26;j++)
                qDebug() << QVariant(kucukharf[j]).toChar();
            for(int j=0;j<10;j++)
                qDebug() << QVariant(sayilar[j]).toChar();
            for(int j=0;j<33;j++)
                qDebug() << QVariant(ozelkarakterler[j]).toChar();
*/


//            for(int j=0;j<=94;j++)
//                dizi[j]=32;


            //Checkboxlara göre dizi[]'ye karakterlerin atanması
            if(ui->checkBox_2->isChecked())
            {
                karaktersayisi = karaktersayisi + 26;
                for(l1=0;l1<26;l1++)
                    dizi[l1+l2+l3+l4]=buyukharf[l1];
            }
            if(ui->checkBox->isChecked())
            {
                karaktersayisi = karaktersayisi + 26;
                for(l2=0;l2<26;l2++)
                    dizi[l1+l2+l3+l4]=kucukharf[l2];
            }
            if(ui->checkBox_3->isChecked())
            {
                karaktersayisi = karaktersayisi + 10;
                for(l3=0;l3<10;l3++)
                    dizi[l1+l2+l3+l4]=sayilar[l3];
            }
            if(ui->checkBox_4->isChecked())
            {
                karaktersayisi = karaktersayisi + 33;
                for(l4=0;l4<33;l4++)
                    dizi[l1+l2+l3+l4]=ozelkarakterler[l4];
            }
//            qDebug() << "Karakter çeşidi sayısı: " << karaktersayisi;

            kelimeboyutu_glob = QVariant(ui->comboBox->currentIndex()).toInt() + 3;
            onek_glob = on_ek.length();
            sonek_glob = son_ek.length();
            karaktersayisi_glob = karaktersayisi;

            dosyaboyut_glob = pow(onek_glob+sonek_glob+karaktersayisi_glob,kelimeboyutu_glob);
/*
//            qDebug()<< kelimeboyutu_glob << " " << onek_glob << " " << sonek_glob << " " << karaktersayisi_glob ;
            dosyaboyutu_son = 5* dosyaboyut_glob/1024;
//            qDebug()<<dosyaboyutu_son;
            if(dosyaboyutu_son<1024)
            {
                birim = " KB";
                //dosyaboyutu_son_string = QString::number(dosyaboyutu_son,'f',1);
                qDebug()<<QVariant(dosyaboyutu_son).toString();
            }
            else if(dosyaboyutu_son>=1024 && dosyaboyutu_son<1048576)
            {
                dosyaboyutu_son = dosyaboyutu_son/1024;
                //dosyaboyutu_son_string = QString::number(dosyaboyutu_son,'f',1);
                birim = " MB";
                qDebug()<<QVariant(dosyaboyutu_son/1024).toString();
            }
            else
            {
                dosyaboyutu_son = dosyaboyutu_son/1024;
                //dosyaboyutu_son_string=QString::number(dosyaboyutu_son,'f',1);
                birim = " GB";
                qDebug()<<QVariant(dosyaboyutu_son/1048576).toString();

            }
            ui->label_14->setText(QVariant(dosyaboyutu_son).toString()+birim);
*/
            //Kullanıcı İşlemi Başlata tıkladığı zaman dosya boyutu,toplam kelime bilgiler verilecek ve
            //İşleme devam etmesi için onay alınacak.(Dosya boyutu ve işlem uzun sürdüğü için sistem yanıt vermeyebilir!)
            mesajkutusustring = "This operation could take a long time\n and may cause the system stuck!";
            mesajkutusu.setText(mesajkutusustring);
            mesajkutusu.setInformativeText("This operation overwrites the existing *.list file!\nAre you sure to continue?");
            mesajkutusu.setStandardButtons(QMessageBox::Yes | QMessageBox::No);
            mesajkutusu.setDefaultButton(QMessageBox::No);
            mesajkutusu.setIcon(QMessageBox::Critical);
            mesajkutusu.setWindowTitle("Warning!");
            int cevap = mesajkutusu.exec();
            switch (cevap) {
            case QMessageBox::Yes:

                ui->progressBar->setValue(0);
                //ui->label_11->setText("Lütfen işlemin tamamlanmasını bekleyin");

                //Dosyaya yazmanın başlaması(Kelime Oluşturma)
                switch (ui->comboBox->currentIndex()) {
                case 0:
                    for(x=0; x<karaktersayisi; x++)
                    {
                        for(y=0; y<karaktersayisi; y++)
                        {
                            for(int z=0; z<karaktersayisi; z++)
                            {
                                //Dosyaya yazma işlemi
                                stream << on_ek;
                                stream << QVariant(dizi[z]).toChar() << QVariant(dizi[y]).toChar() << QVariant(dizi[x]).toChar();
                                stream << son_ek << endl;
                                ui->progressBar->setValue(progress_sayac+100/(pow(karaktersayisi,kelimeboyutu_glob)));
                                progress_sayac++;
                            }
                        }
                    }
                    break;
                case 1:
                    for(x=0; x<karaktersayisi; x++)
                    {
                        for(y=0; y<karaktersayisi; y++)
                        {
                            for(z=0; z<karaktersayisi; z++)
                            {
                                for(t=0; t<karaktersayisi; t++)
                                {
                                    //Dosyaya yazma işlemi
                                    stream << on_ek;
                                    stream << QVariant(dizi[t]).toChar() << QVariant(dizi[z]).toChar() << QVariant(dizi[y]).toChar() << QVariant(dizi[x]).toChar();
                                    stream << son_ek << endl;
                                    ui->progressBar->setValue(progress_sayac*100/(pow(karaktersayisi,kelimeboyutu_glob)));
                                    progress_sayac++;
                                }
                            }
                        }
                    }
                    break;
                case 2:
                    for(x=0; x<karaktersayisi; x++)
                    {
                        for(y=0; y<karaktersayisi; y++)
                        {
                            for(z=0; z<karaktersayisi; z++)
                            {
                                for(t=0; t<karaktersayisi; t++)
                                {
                                    for(w=0; w<karaktersayisi; w++)
                                    {
                                        //Dosyaya yazma işlemi
                                        stream << on_ek;
                                        stream << QVariant(dizi[w]).toChar() << QVariant(dizi[t]).toChar() << QVariant(dizi[z]).toChar() << QVariant(dizi[y]).toChar() << QVariant(dizi[x]).toChar();
                                        stream << son_ek << endl;
                                        ui->progressBar->setValue(progress_sayac*100/(pow(karaktersayisi,kelimeboyutu_glob)));
                                        progress_sayac++;
                                    }
                                }
                            }
                        }
                    }
                    break;
                case 3:
                    for(x=0; x<=karaktersayisi; x++)
                    {
                        for(y=0; y<=karaktersayisi; y++)
                        {
                            for(z=0; z<=karaktersayisi; z++)
                            {
                                for(t=0; t<=karaktersayisi; t++)
                                {
                                    for(w=0; w<=karaktersayisi; w++)
                                    {
                                        for(q=0; q<=karaktersayisi; q++)
                                        {
                                            //Dosyaya yazma işlemi
                                            stream << on_ek;
                                            stream << QVariant(dizi[q]).toChar() << QVariant(dizi[w]).toChar() << QVariant(dizi[t]).toChar() << QVariant(dizi[z]).toChar() << QVariant(dizi[y]).toChar() << QVariant(dizi[x]).toChar();
                                            stream << son_ek << endl;
                                            ui->progressBar->setValue(progress_sayac*100/(pow(karaktersayisi,kelimeboyutu_glob)));
                                            progress_sayac++;
                                        }
                                    }
                                }
                            }
                        }
                    }
                    break;
                case 4:
                    for(x=0; x<=karaktersayisi; x++)
                    {
                        for(y=0; y<=karaktersayisi; y++)
                        {
                            for(z=0; z<=karaktersayisi; z++)
                            {
                                for(t=0; t<=karaktersayisi; t++)
                                {
                                    for(w=0; w<=karaktersayisi; w++)
                                    {
                                        for(q=0; q<=karaktersayisi; q++)
                                        {
                                            for(m=0; m<=karaktersayisi; m++)
                                            {
                                                //Dosyaya yazma işlemi
                                                stream << on_ek;
                                                stream << QVariant(dizi[6]).toChar() << QVariant(dizi[5]).toChar() << QVariant(dizi[4]).toChar() << QVariant(dizi[3]).toChar() << QVariant(dizi[2]).toChar() << QVariant(dizi[1]).toChar() << QVariant(dizi[0]).toChar();
                                                stream << son_ek << endl;
                                                ui->progressBar->setValue(progress_sayac*100/(pow(karaktersayisi,kelimeboyutu_glob)));
                                                progress_sayac++;
                                            }
                                        }
                                    }
                                }
                            }
                        }
                    }
                    break;
                case 5:
                    for(x=0; x<=karaktersayisi; x++)
                    {
                        for(y=0; y<=karaktersayisi; y++)
                        {
                            for(z=0; z<=karaktersayisi; z++)
                            {
                                for(t=0; t<=karaktersayisi; t++)
                                {
                                    for(w=0; w<=karaktersayisi; w++)
                                    {
                                        for(q=0; q<=karaktersayisi; q++)
                                        {
                                            for(m=0; m<=karaktersayisi; m++)
                                            {
                                                for(n=0; n<=karaktersayisi; n++)
                                                {
                                                    //Dosyaya yazma işlemi
                                                    stream << on_ek;
                                                    stream << QVariant(dizi[7]).toChar() << QVariant(dizi[6]).toChar() << QVariant(dizi[5]).toChar() << QVariant(dizi[4]).toChar() << QVariant(dizi[3]).toChar() << QVariant(dizi[2]).toChar() << QVariant(dizi[1]).toChar() << QVariant(dizi[0]).toChar();
                                                    stream << son_ek << endl;
                                                    ui->progressBar->setValue(progress_sayac*100/(pow(karaktersayisi,kelimeboyutu_glob)));
                                                    progress_sayac++;
                                                }
                                            }
                                        }
                                    }
                                }
                            }
                        }
                    }
                    break;
                case 6:
                    for(x=0; x<=karaktersayisi; x++)
                    {
                        for(y=0; y<=karaktersayisi; y++)
                        {
                            for(z=0; z<=karaktersayisi; z++)
                            {
                                for(t=0; t<=karaktersayisi; t++)
                                {
                                    for(w=0; w<=karaktersayisi; w++)
                                    {
                                        for(q=0; q<=karaktersayisi; q++)
                                        {
                                            for(m=0; m<=karaktersayisi; m++)
                                            {
                                                for(n=0; n<=karaktersayisi; n++)
                                                {
                                                    for(g=0; g<=karaktersayisi; g++)
                                                    {
                                                        //Dosyaya yazma işlemi
                                                        stream << on_ek;
                                                        stream << QVariant(dizi[8]).toChar() << QVariant(dizi[7]).toChar() << QVariant(dizi[6]).toChar() << QVariant(dizi[5]).toChar() << QVariant(dizi[4]).toChar() << QVariant(dizi[3]).toChar() << QVariant(dizi[2]).toChar() << QVariant(dizi[1]).toChar() << QVariant(dizi[0]).toChar();
                                                        stream << son_ek << endl;
                                                        ui->progressBar->setValue(progress_sayac*100/(pow(karaktersayisi,kelimeboyutu_glob)));
                                                        progress_sayac++;
                                                    }
                                                }
                                            }
                                        }
                                    }
                                }
                            }
                        }
                    }
                    break;
                case 7:
                    for(x=0; x<=karaktersayisi; x++)
                    {
                        for(y=0; y<=karaktersayisi; y++)
                        {
                            for(z=0; z<=karaktersayisi; z++)
                            {
                                for(t=0; t<=karaktersayisi; t++)
                                {
                                    for(w=0; w<=karaktersayisi; w++)
                                    {
                                        for(q=0; q<=karaktersayisi; q++)
                                        {
                                            for(m=0; m<=karaktersayisi; m++)
                                            {
                                                for(n=0; n<=karaktersayisi; n++)
                                                {
                                                    for(g=0; g<=karaktersayisi; g++)
                                                    {
                                                        for(h=0; h<=karaktersayisi; h++)
                                                        {
                                                            //Dosyaya yazma işlemi
                                                            stream << on_ek;
                                                            stream << QVariant(dizi[9]).toChar() << QVariant(dizi[8]).toChar() << QVariant(dizi[7]).toChar() << QVariant(dizi[6]).toChar() << QVariant(dizi[5]).toChar() << QVariant(dizi[4]).toChar() << QVariant(dizi[3]).toChar() << QVariant(dizi[2]).toChar() << QVariant(dizi[1]).toChar() << QVariant(dizi[0]).toChar();
                                                            stream << son_ek << endl;
                                                            ui->progressBar->setValue(progress_sayac*100/(pow(karaktersayisi,kelimeboyutu_glob)));
                                                            progress_sayac++;
                                                        }
                                                    }
                                                }
                                            }
                                        }
                                    }
                                }
                            }
                        }
                    }
                    break;
                }

                // Ascii sınırları
                /*
                //progress bar'ı en dıştaki döngünün içine koyup artış değerini hesaplat!
                ui->progressBar->setValue(ui->progressBar->value()+4);
                */
                // uçbirim çıktısı
                qDebug("Operation completed!");

                //ui->label_11->setText("İşlem Tamamlandı");
                // İşlem bitti
                //ui->progressBar->setValue(100);
                file.close();
                break;

            case QMessageBox::No:
                qDebug()<< "Operation has canceled by user!";
                //qApp->quit();
                //ui->label_11->setText("İşlem kullanıcı tarafından iptal edildi!");
                break;
            }





        }

        //Dosyayı kapatır

        //    QTimer timer1;
        //    ui->label_14->setText(QString::number(timer1.interval());
        //    QTimer::singleShot(3000, &a, SLOT(quit()));
        //    timer1.setInterval(60);
        //    timer1.start(10);
        //    qDebug()<< timer1.interval();


    }
}

void MainWindow::on_actionHakk_nda_triggered()
{
    // Yeni satır için \n kullan.
    QMessageBox::information(NULL,"About","This software is created by Samet Kamgul.\nContact:  metaltrrocker@yahoo.com.tr");
}

void MainWindow::on_pushButton_2_clicked()
{
    // Uygulamadan direk çıkış yapar
    //

    // Uygulamadan direk çıkış yapar Alternatif olarak
    //QApplication::quit();
    // alttaki ile farkını araştırmadım
    //qApp->quit();
    exit(1);

    // Yeni form oluşturur.
    QProcess::startDetached(qApp->arguments()[0], qApp->arguments());
}

void MainWindow::on_actionFormu_Temizle_triggered()
{
    //Formu Temizleme
    ui->comboBox->setCurrentIndex(0);
    ui->checkBox->setChecked(false);
    ui->checkBox_2->setChecked(false);
    ui->checkBox_3->setChecked(false);
    ui->checkBox_4->setChecked(false);
    ui->lineEdit->clear();
    ui->lineEdit_2->clear();
    ui->progressBar->setValue(0);
    //ui->label_11->setText("Lütfen Kelime Uzunluğunu Ayarlayın");
    //ui->label_14->setText("İşlemin Başlaması Bekleniyor!");
}

void MainWindow::on_actionKullan_m_triggered()
{
    QMessageBox::information(NULL,"Usage","You can use this software to create passwords for bruteforce.\nWordlist will created as *.list file in the executable file's directory. \nPlease make sure there is empty space on your disk.");
}


