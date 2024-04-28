#include <iostream>
#include <riscv-vector.h>
#include <random>
vfloat32m4_t my_erf0(vfloat32m4_t x, int vl)
{
    float a1 = (float)0.254829592;
    float a2 = (float)-0.284496736;
    float a3 = (float)1.421413741;
    float a4 = (float)-1.453152027;
    float a5 = (float)1.061405429;
    float p = (float)0.3275911;
    vint32m4_t sign;
    vint32m4_t floatcast = vreinterpret_v_f32m4_i32m4(x);
    sign = vsra_vx_i32m4(floatcast, 31, vl);
    sign = vor_vx_i32m4(sign, 1, vl);
    vfloat32m4_t float_sign = vfcvt_f_x_v_f32m4(sign, vl);

    vfloat32m4_t x_abs = vfmul_vv_f32m4(float_sign, x, vl);

    vfloat32m4_t oper1 = vfmul_vf_f32m4(x_abs, p, vl);
    oper1 = vfadd_vf_f32m4(oper1, 1.0f, vl);
    vfloat32m4_t vect1 = vfmv_v_f_f32m4(1.0f, vl);
    vfloat32m4_t t = vfdiv_vv_f32m4(vect1, oper1, vl);

    vfloat32m4_t oper2 = vfmul_vf_f32m4(t, a5, vl);
    oper2 = vfadd_vf_f32m4(oper2, a4, vl);
    oper2 = vfmul_vv_f32m4(oper2, t, vl);
    oper2 = vfadd_vf_f32m4(oper2, a3, vl);
    oper2 = vfmul_vv_f32m4(oper2, t, vl);
    oper2 = vfadd_vf_f32m4(oper2, a2, vl);
    oper2 = vfmul_vv_f32m4(oper2, t, vl);
    oper2 = vfadd_vf_f32m4(oper2, a1, vl);
    oper2 = vfmul_vv_f32m4(oper2, t, vl);

    vfloat32m4_t minus_x = vfmul_vf_f32m4(x, -1.0f, vl);
    vfloat32m4_t minus_x_mult_x = vfmul_vv_f32m4(x, minus_x, vl);
    vfloat32m4_t exp_x_x = my_exp0(minus_x_mult_x, vl);

    oper2 = vfmul_vv_f32m4(oper2, exp_x_x, vl);
    vfloat32m4_t y = vfsub_vv_f32m4(vect1, oper2, vl);


    vfloat32m4_t y_mult_sign = vfmul_vv_f32m4(y, float_sign, vl);
    return y_mult_sign;

}
int main()
{
    std::default_random_engine rd(0);//генератор случайных чисел
    std::uniform_real_distribution<float> dist1(-5.0f, 10.0f);
    float* S0 = new float[16];
    float* my_erf = new float[16];
    float* erf = new float[16];

    for (int i = 0; i < 16; i++)
    {

        S0[i] = dist1(rd);
    }

    vfloat32m4_t so = vle_v_f32m4(S0, 16);
    vfloat32m4_t exp_val = my_erf0(S0, 16);
    vse_v_f32m4(my_exponent, exp_val, 16);

    for (int i = 0; i < 16; i++)
    {
        exponent[i] = erf(S0[i]);
    }
    float* diff = new float[16];
    float max_diff = 0.0f;
    for (int i = 0; i < 16; i++)
    {
        diff[i] = abs(my_erf[i] - erf[i]);
        if (diff[i] > max_diff) max_diff = diff[i];
        printf("x=%.12ef\nmy_erf=%.12ef\nerf=%.12ef\ndiff=%i  max_diff=%i\n",
            S0[i], my_erf[i], erf[i], diff[i], max_diff);
    }






    return 0;
}