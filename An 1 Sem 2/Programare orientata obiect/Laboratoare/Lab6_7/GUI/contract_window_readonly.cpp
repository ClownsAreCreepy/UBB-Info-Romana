#include "contract_window_readonly.h"


ContractWindowROnly::ContractWindowROnly(ServiceDisciplina &serv, QWidget *parent) : QWidget(parent),
    service(serv) {
    service.addObserver(this);
    this->setMinimumSize(400, 400);
}


void ContractWindowROnly::paintEvent(QPaintEvent * /*event*/) {
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);
    painter.setRenderHint(QPainter::SmoothPixmapTransform);

    const auto &contract = service.contract_getAll();

    // static = incarcam o data
    static vector<QImage> imaginiIncarcate;
    static bool incarcat = false;

    if (!incarcat) {
        const vector<QString> imagini = {
            R"(Imagini\Oreo_bonk.jpg)",
            R"(Imagini\Oreo_cer.jpg)",
            R"(Imagini\Oreo_close_up.jpg)",
            R"(Imagini\Oreo_first.jpg)",
            R"(Imagini\Oreo_fotomodel.jpg)",
            R"(Imagini\Oreo_frunza.jpg)",
            R"(Imagini\Oreo_geam.jpg)",
            R"(Imagini\Oreo_ground.jpg)",
            R"(Imagini\Oreo_half.jpg)",
            R"(Imagini\Oreo_long.jpg)",
            R"(Imagini\Oreo_majestic.jpg)",
            R"(Imagini\Oreo_noapte.jpg)",
            R"(Imagini\Oreo_nose.jpg)",
            R"(Imagini\Oreo_sniff.jpg)",
            R"(Imagini\Oreo_sniffier.jpg)",
            R"(Imagini\Oreo_toanta.jpg)",
            R"(Imagini\Oreo_top_down.jpg)",
            R"(Imagini\Oreo_usa.jpg)",
            R"(Imagini\Oreo_walk.jpg)",
            R"(Imagini\Oreo_worried.jpg)",
            R"(Imagini\Oreo_yawn.jpg)",
        };

        for (const auto &path: imagini)
            imaginiIncarcate.emplace_back(QImage(path));

        incarcat = true;
    }

    constexpr int size = 128;

    uniform_int_distribution<size_t> imgDist(0, imaginiIncarcate.size() - 1);
    uniform_int_distribution xDist(0, width() - size);
    uniform_int_distribution yDist(0, height() - size);

    for (size_t i = 0; i < contract.size(); ++i) {
        const QImage &icon = imaginiIncarcate[imgDist(rng)];
        const int x = xDist(rng);
        const int y = yDist(rng);

        if (!icon.isNull())
            painter.drawImage(x, y, icon.scaled(size, size, Qt::KeepAspectRatio, Qt::SmoothTransformation));
        else {
            painter.setPen(Qt::red);
            painter.drawText(QRect(x, y, size, size), Qt::AlignCenter, "Failed to load :(");
        }
    }
}


ContractWindowROnly::~ContractWindowROnly() {
    service.removeObserver(this);
}


void ContractWindowROnly::update() {
    this->repaint();
}
