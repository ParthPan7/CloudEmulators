#include <QApplication>
#include <QLabel>
#include <aws/core/Aws.h>
#include <aws/core/Aws.h>
#include <aws/s3/S3Client.h>
#include <aws/s3/model/ListBucketsRequest.h>
#include <iostream>

int main(int argc, char *argv[])
{
    // Init AWScd
     Aws::SDKOptions options;
     Aws::InitAPI(options);
     {
         Aws::S3::S3Client s3_client;
         auto outcome = s3_client.ListBuckets();
         if (outcome.IsSuccess()) {
             std::cout << "Buckets:\n";
             for (auto const &bucket : outcome.GetResult().GetBuckets()) {
                 std::cout << "  " << bucket.GetName() << std::endl;
             }
         } else {
             std::cerr << "Error listing buckets: "
                       << outcome.GetError().GetMessage() << std::endl;
         }
     }

    QApplication app(argc, argv);
    QLabel label("Qt + AWS SDK (Windows Ready)");
    label.resize(400, 200);
    label.show();

    int ret = app.exec();
    Aws::ShutdownAPI(options);
    return ret;
}
