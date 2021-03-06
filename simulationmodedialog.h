#ifndef SIMULATIONMODEDIALOG_H
#define SIMULATIONMODEDIALOG_H

#include <QDialog>
#include <QGridLayout>
#include <QLabel>
#include <QCheckBox>
#include <QSlider>
#include <QLineEdit>
#include <QPushButton>
#include <QCheckBox>
#include <QComboBox>
#include <QHBoxLayout>
#include <QStatusBar>
#include "commonunits.h"

class SimulationModeDialog : public QDialog
{
    Q_OBJECT
public:
    explicit SimulationModeDialog(const QString title, QWidget *parent = 0);

signals:
    void writeSimulationInputValues(bool enableSimMode,
                                    SimulationInputValues values,
                                    SimulationInputChanges changes);
private:
    QGridLayout *m_grid;
    QHBoxLayout *m_buttonLayout;
    QStatusBar *m_statusBar;

    QLabel *m_inertiaSwitchLabel;
    QLabel *m_heatedScreenLabel;
    QLabel *m_mafLabel;
    QLabel *m_mafTrimLabel;
    QLabel *m_throttlePositionLabel;
    QLabel *m_coolantTempLabel;
    QLabel *m_fuelTempLabel;
    QLabel *m_neutralSwitchLabel;
    QLabel *m_airConLoadLabel;
    QLabel *m_mainRelayLabel;
    QLabel *m_tuneResistorLabel;
    QLabel *m_o2SensorReferenceLabel;
    QLabel *m_diagnosticPlugLabel;
    QLabel *m_o2OddDutyLabel;
    QLabel *m_o2EvenDutyLabel;

    QLabel *m_inertiaSwitchVal;
    QLabel *m_heatedScreenVal;
    QLabel *m_mafVal;
    QLabel *m_mafTrimVal;
    QLabel *m_throttlePositionVal;
    QLabel *m_coolantTempVal;
    QLabel *m_fuelTempVal;
    QLabel *m_neutralSwitchVal;
    QLabel *m_airConLoadVal;
    QLabel *m_mainRelayVal;
    QLabel *m_tuneResistorVal;
    QLabel *m_o2SensorReferenceVal;
    QLabel *m_diagnosticPlugVal;
    QLabel *m_o2OddDutyVal;
    QLabel *m_o2EvenDutyVal;

    QLineEdit *m_inertiaSwitchRawVal;
    QLineEdit *m_heatedScreenRawVal;
    QLineEdit *m_mafRawVal;
    QLineEdit *m_mafTrimRawVal;
    QLineEdit *m_throttlePositionRawVal;
    QLineEdit *m_coolantTempRawVal;
    QLineEdit *m_fuelTempRawVal;
    QLineEdit *m_neutralSwitchRawVal;
    QLineEdit *m_airConLoadRawVal;
    QLineEdit *m_mainRelayRawVal;
    QLineEdit *m_tuneResistorRawVal;
    QLineEdit *m_o2SensorReferenceRawVal;
    QLineEdit *m_diagnosticPlugRawVal;
    QLineEdit *m_o2OddDutyRawVal;
    QLineEdit *m_o2EvenDutyRawVal;

    QCheckBox *m_inertiaSwitchBox;
    QCheckBox *m_heatedScreenBox;
    QCheckBox *m_airConLoadBox;
    QCheckBox *m_diagnosticPlugBox;
    QComboBox *m_neutralSwitchBox;
    QSlider *m_mafSlider;
    QSlider *m_mafTrimSlider;
    QSlider *m_coolantTempSlider;
    QSlider *m_fuelTempSlider;
    QSlider *m_throttleSlider;
    QSlider *m_mainRelaySlider;
    QSlider *m_o2OddDutySlider;
    QSlider *m_o2EvenDutySlider;

    QPushButton *m_enableSimModeButton;
    QPushButton *m_writeButton;
    QPushButton *m_closeButton;

    SimulationInputChanges m_changes;

    void setupWidgets();
    double Peak_LorentzianModifiedPeakG_model(double x_in);
    unsigned int convertVoltageToQuadraticCounts(float voltage);
    void doWrite(bool enableSimMode);

private slots:
    void onEnabledSimModeClicked();
    void onWriteClicked();
    void onCloseClicked();

    void onWriteSuccess();
    void onWriteFailure();

    void onMafChanged(int val);
    void onMafTrimChanged(int val);
    void onInertiaSwitchChanged(bool checked);
    void onHeatedScreenChanged(bool checked);
    void onNeutralSwitchChanged(int val);
    void onCoolantTempChanged(int val);
    void onFuelTempChanged(int val);
    void onThrottleChanged(int val);
    void onMainRelayVoltageChanged(int val);
    void onAirConLoadChanged(bool checked);
    void onDiagnosticPlugChanged(bool checked);
    void onO2OddDutyChanged(int val);
    void onO2EvenDutyChanged(int val);
};

#endif // SIMULATIONMODEDIALOG_H
