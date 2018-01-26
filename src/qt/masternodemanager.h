#ifndef MASTERNODEMANAGER_H
#define MASTERNODEMANAGER_H

#include "util.h"
#include "sync.h"

#include <QWidget>
#include <QTimer>
#include <QFuture>
#include <QTableWidget>

#define MASTERNODELIST_UPDATE_SECONDS 15

namespace Ui {
    class MasternodeManager;
}
class ClientModel;
class WalletModel;

QT_BEGIN_NAMESPACE
class QModelIndex;
QT_END_NAMESPACE


struct MasternodeRow {
    QTableWidgetItem *activeItem;
    QTableWidgetItem *addressItem;
    QTableWidgetItem *rankItem;
    QTableWidgetItem *activeSecondsItem;
    QTableWidgetItem *lastSeenItem;
    QTableWidgetItem *pubkeyItem;
};

/** Masternode Manager page widget */
class MasternodeManager : public QWidget
{
    Q_OBJECT

public:
    explicit MasternodeManager(QWidget *parent = 0);
    ~MasternodeManager();

    void setClientModel(ClientModel *clientModel);
    void setWalletModel(WalletModel *walletModel);


public slots:
    void updateNodeList();
    void updateNodeListConc();
    void updateAdrenalineNode(QString alias, QString addr, QString privkey, QString collateral);
    void filterMasternodeList();

signals:

private:
    QTimer *timer;
    Ui::MasternodeManager *ui;
    ClientModel *clientModel;
    WalletModel *walletModel;
    CCriticalSection cs_adrenaline;
    QFuture<void> f1;
    void subscribeToCoreSignals();
    void unsubscribeFromCoreSignals();
    std::vector<MasternodeRow> masternodeTableRows;

private slots:
    void on_copyAddressButton_clicked();
    void on_createButton_clicked();
    void on_editButton_clicked();
    void on_getConfigButton_clicked();
    void on_startButton_clicked();
    void on_stopButton_clicked();
    void on_startAllButton_clicked();
    void on_stopAllButton_clicked();
    void on_removeButton_clicked();
    void on_tableWidget_2_itemSelectionChanged();
    void updateMasternodeTable();
};

#endif // MASTERNODEMANAGER_H
