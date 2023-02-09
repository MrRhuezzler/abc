vector<vector<float> > Multiply(const vector<vector<float> >& A, const vector<vector<float> >& B) {
    vector<vector<float> > C =  vector<vector<float> >(3, vector<float>(3, 1));
    for(int i = 0; i < 3; i++) {
            for(int j = 0; j < 3; j++) {
                float sum = 0;
                for(int k = 0; k < 3; k++) {
                    sum += A[i][k] * B[k][j];
                }
                C[i][j] = sum;
            }
    }
    return C;
}

vector<vector<float> > Translate(float tx, float ty) {
    vector<vector<float> > mat =  vector<vector<float> >(3, vector<float>(3, 1));
    mat[0][0] = 1;
    mat[0][1] = 0;
    mat[0][2] = tx;
    mat[1][0] = 0;
    mat[1][1] = 1;
    mat[1][2] = ty;
    mat[2][0] = 0;
    mat[2][1] = 0;
    mat[2][2] = 1;
    return mat;
}

vector<vector<float> > Rotate(float deg) {
    float rad = deg * (M_PI / 180);
    vector<vector<float> > mat =  vector<vector<float> >(3, vector<float>(3, 1));
    mat[0][0] = cos(rad);
    mat[0][1] = -sin(rad);
    mat[0][2] = 0;
    mat[1][0] = sin(rad);
    mat[1][1] = cos(rad);
    mat[1][2] = 0;
    mat[2][0] = 0;
    mat[2][1] = 0;
    mat[2][2] = 1;
    return mat;
}

vector<vector<float> > Rotate(float deg, float x, float y) {
    return Multiply(Translate(x, y), Multiply(Rotate(deg), Translate(-x, -y)));;
}

vector<vector<float> > Scale(float sx, float sy) {
    vector<vector<float> > mat =  vector<vector<float> >(3, vector<float>(3, 1));
    mat[0][0] = sx;
    mat[0][1] = 0;
    mat[0][2] = 0;
    mat[1][0] = 0;
    mat[1][1] = sy;
    mat[1][2] = 0;
    mat[2][0] = 0;
    mat[2][1] = 0;
    mat[2][2] = 1;
    return mat;
}

vector<vector<float> > Scale(float sx, float sy, float x, float y) {
    vector<vector<float> > mat =  vector<vector<float> >(3, vector<float>(3, 1));
    return Multiply(Translate(x, y), Multiply(Scale(sx, sy), Translate(-x, -y)));;
}
