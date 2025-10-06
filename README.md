
# CloudEmulators

Emulator or mimic any cloud provider services without provising cloud provider resources to gauge your infrastructure needs locally. 

---

## Features

- Local AWS Emulator using **LocalStack**
- Emulates services: **S3, DynamoDB, EC2, Lambda, CloudWatch**
- Infrastructure-as-Code with **Terraform**
- Easy setup via **Docker Compose**
- Compatible with **AWS CLI** configured to use LocalStack
- Fully open-source, can be extended to other AWS services

---

## Prerequisites

- Linux (tested on Ubuntu)
- Docker & Docker Compose
- Terraform
- AWS CLI v2
- Python 3.10+ (optional, for virtual environments)

---

## AWS Local Environment Setup Instructions

### 1. Clone the Repository

```
git clone https://github.com/ParthPan7/CloudEmulators.git

cd CloudEmulations
```

### 2. Start LocalStack

```
docker-compose up -d
```

Check logs:

```
docker logs -f localstack
```

### 3. Configure AWS CLI

```
aws configure


- AWS Access Key ID: test  
- AWS Secret Access Key: test  
- Default region: us-east-1  
- Output format: json  
```
Test:

```
aws --endpoint-url=http://localhost:4566 s3 ls
aws --endpoint-url=http://localhost:4566 dynamodb list-tables
```

### 4. Terraform Setup

```
cd terraform/aws
terraform init
terraform apply
terraform destroy  # when done
```

```
aws --endpoint-url=http://localhost:4566 s3 ls
aws --endpoint-url=http://localhost:4566 dynamodb list-tables
```


