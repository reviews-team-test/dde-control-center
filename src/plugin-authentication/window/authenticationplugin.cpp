#include "authenticationplugin.h"

#include "charamangermodel.h"
#include "charamangerworker.h"
#include "faceiddetailwidget.h"
#include "fingerdetailwidget.h"
#include "irisdetailwidget.h"

QString AuthenticationPlugin::name() const
{
    return QStringLiteral("Authentication");
}

ModuleObject *AuthenticationPlugin::module()
{
    // 一级
    AuthenticationModule *authenticationInterface = new AuthenticationModule;
    authenticationInterface->setChildType(ModuleObject::HList);

    // 二级 -- 指纹
    ModuleObject *moduleFinger = new ModuleObject("fingerprint", tr("Fingerprint"), this);
    moduleFinger->setChildType(ModuleObject::Page);
    FingerModule *fingerPage = new FingerModule(authenticationInterface->model(), authenticationInterface->work());
    moduleFinger->appendChild(fingerPage);
    authenticationInterface->appendChild(moduleFinger);

    // 二级 -- 人脸
    ModuleObject *moduleFace = new ModuleObject("face", tr("Face"), this);
    moduleFace->setChildType(ModuleObject::Page);
    FaceModule *facePage = new FaceModule(authenticationInterface->model(), authenticationInterface->work());
    moduleFace->appendChild(facePage);
    authenticationInterface->appendChild(moduleFace);

    // 二级 -- 虹膜
    ModuleObject *moduleIris= new ModuleObject("iris", tr("Iris"), this);
    moduleIris->setChildType(ModuleObject::Page);
    IrisModule *irisPage = new IrisModule(authenticationInterface->model(), authenticationInterface->work());
    moduleIris->appendChild(irisPage);
    authenticationInterface->appendChild(moduleIris);

    return authenticationInterface;
}

int AuthenticationPlugin::location() const
{
    return 3;
}

AuthenticationModule::AuthenticationModule(QObject *parent)
    : ModuleObject("authentication", tr("Biometric Authentication"), tr("Biometric Authentication"), QIcon::fromTheme("dcc_nav_authentication"), parent)
    , m_model(new CharaMangerModel(this))
    , m_work(new CharaMangerWorker(m_model, this))
{

}

AuthenticationModule::~AuthenticationModule()
{
    m_model->deleteLater();
    m_work->deleteLater();
}

void AuthenticationModule::active()
{

}

QWidget *FingerModule::page()
{
    FingerDetailWidget *w = new FingerDetailWidget;
    w->setFingerModel(m_model);
    connect(w, &FingerDetailWidget::requestAddThumbs, m_worker, &CharaMangerWorker::tryEnroll);
    connect(w, &FingerDetailWidget::requestStopEnroll, m_worker, &CharaMangerWorker::stopFingerEnroll);
    connect(w, &FingerDetailWidget::requestDeleteFingerItem, m_worker, &CharaMangerWorker::deleteFingerItem);
    connect(w, &FingerDetailWidget::requestRenameFingerItem, m_worker, &CharaMangerWorker::renameFingerItem);
    connect(w, &FingerDetailWidget::noticeEnrollCompleted, m_worker, &CharaMangerWorker::refreshFingerEnrollList);
    return w;
}

QWidget *FaceModule::page()
{
    FaceidDetailWidget *w = new FaceidDetailWidget(m_model);
    connect(w, &FaceidDetailWidget::requestEntollStart, m_worker, &CharaMangerWorker::entollStart);
    connect(w, &FaceidDetailWidget::requestStopEnroll, m_worker, &CharaMangerWorker::stopEnroll);
    connect(w, &FaceidDetailWidget::requestDeleteFaceItem, m_worker, &CharaMangerWorker::deleteCharaItem);
    connect(w, &FaceidDetailWidget::requestRenameFaceItem, m_worker, &CharaMangerWorker::renameCharaItem);
    connect(w, &FaceidDetailWidget::noticeEnrollCompleted, m_worker, &CharaMangerWorker::refreshUserEnrollList);
    return w;
}

QWidget *IrisModule::page()
{
    IrisDetailWidget *w = new IrisDetailWidget(m_model);
    connect(w, &IrisDetailWidget::requestEntollStart, m_worker, &CharaMangerWorker::entollStart);
    connect(w, &IrisDetailWidget::requestStopEnroll, m_worker, &CharaMangerWorker::stopEnroll);
    connect(w, &IrisDetailWidget::requestDeleteIrisItem, m_worker, &CharaMangerWorker::deleteCharaItem);
    connect(w, &IrisDetailWidget::requestRenameIrisItem, m_worker, &CharaMangerWorker::renameCharaItem);
    connect(w, &IrisDetailWidget::noticeEnrollCompleted, m_worker, &CharaMangerWorker::refreshUserEnrollList);
    return w;
}
