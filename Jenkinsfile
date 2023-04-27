pipeline {
        agent { label 'transliterator-backend-agent' }

        environment {
                DOCKERHUB_CREDENTIALS = credentials('dockerhub-markdurkot')
                BACKEND_KEYS = credentials('backend-keys')
                BACKEND_DNS = '3.140.39.147'
        }

        stages {
                stage('Build & Test') {
                        steps {
                                sh 'docker build -t markdurkot/transliterator-backend:latest .'
                        }
                }

                stage('Deploy') {
                        steps {
                                // login to docker
                                sh 'echo $DOCKERHUB_CREDENTIALS_PSW | docker login -u $DOCKERHUB_CREDENTIALS_USR --password-stdin'

                                // push docker container
                                sh 'docker push markdurkot/transliterator-backend:latest'

                                // copy startup script to host
                                sh 'scp -o StrictHostKeyChecking=no -i $BACKEND_KEYS startup.sh ec2-user@$BACKEND_DNS:~'

                                // launch startup script on host
                                sh 'ssh -o StrictHostKeyChecking=no -i $BACKEND_KEYS ec2-user@$BACKEND_DNS \'bash -s\' < startup.sh'
                        }

                }
        }

        post {
                always {
                        sh 'docker logout'
                }
        }
}
