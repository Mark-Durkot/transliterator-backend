pipeline{

        agent any

        environment {
                DOCKERHUB_CREDENTIALS=credentials('dockerhub-markdurkot')
        }

        stages {

                stage('Build') {

                        steps {
                                sh 'docker build -t transliterator/transliterator-backend:latest .'
                        }
                }

                stage('Login') {

                        steps {
                                sh 'echo $DOCKERHUB_CREDENTIALS_PSW | docker login -u $DOCKERHUB_CREDENTIALS_USR --password-stdin'
                        }
                }

                stage('Push') {

                        steps {
                                sh 'docker push transliterator/transliterator-backend:latest'
                        }
                }
        }

        post {
                always {
                        sh 'docker logout'
                }
        }

}
